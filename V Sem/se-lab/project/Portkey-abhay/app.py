"""Flask application for Portkey food ordering app."""

import os
import hashlib
from decimal import Decimal
from flask import Flask, render_template, request, redirect, url_for, session, flash
from dotenv import load_dotenv
from db import SessionLocal
from models import Restaurant, MenuItem, CartItem, User
from functools import wraps

# Load environment variables
load_dotenv()

# Initialize Flask app
app = Flask(__name__)
app.config['SECRET_KEY'] = os.urandom(24)
app.config['SESSION_TYPE'] = 'filesystem'


def hash_password(password):
    """Hash a password using SHA-256."""
    return hashlib.sha256(password.encode()).hexdigest()


def login_required(f):
    """Decorator for routes that require login."""
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if 'user_id' not in session:
            flash('Please login to access this page.', 'info')
            return redirect(url_for('login'))
        return f(*args, **kwargs)
    return decorated_function


def get_current_user():
    """Get the current logged-in user."""
    if 'user_id' not in session:
        return None
    db = SessionLocal()
    try:
        user = db.query(User).filter_by(id=session['user_id']).first()
        return user
    finally:
        db.close()


def get_session_id():
    """Get or create a session ID for the current user."""
    if 'session_id' not in session:
        session['session_id'] = os.urandom(16).hex()
    return session['session_id']


def get_cart_count():
    """Get the number of items in the current user's cart."""
    session_id = session.get('session_id')
    if not session_id:
        return 0
    
    db = SessionLocal()
    try:
        count = db.query(CartItem).filter_by(session_id=session_id).count()
        return count
    finally:
        db.close()


def get_cart_total():
    """Calculate the total for the current user's cart."""
    session_id = session.get('session_id')
    if not session_id:
        return Decimal('0.00')
    
    db = SessionLocal()
    try:
        cart_items = db.query(CartItem).filter_by(session_id=session_id).all()
        total = sum(item.subtotal for item in cart_items)
        return Decimal(str(total))
    finally:
        db.close()


@app.route('/login', methods=['GET', 'POST'])
def login():
    """User login page."""
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        db = SessionLocal()
        try:
            user = db.query(User).filter_by(username=username).first()
            
            if user and user.password_hash == hash_password(password):
                session['user_id'] = user.id
                session['username'] = user.username
                flash('Welcome back!', 'success')
                return redirect(url_for('index'))
            else:
                flash('Invalid username or password.', 'error')
        finally:
            db.close()
    
    return render_template('login.html', cart_count=0)


@app.route('/register', methods=['GET', 'POST'])
def register():
    """User registration page."""
    if request.method == 'POST':
        username = request.form.get('username')
        email = request.form.get('email')
        password = request.form.get('password')
        confirm_password = request.form.get('confirm_password')
        
        if password != confirm_password:
            flash('Passwords do not match.', 'error')
            return render_template('register.html', cart_count=0)
        
        db = SessionLocal()
        try:
            # Check if username or email already exists
            existing_user = db.query(User).filter(
                (User.username == username) | (User.email == email)
            ).first()
            
            if existing_user:
                flash('Username or email already exists.', 'error')
                db.close()
                return render_template('register.html', cart_count=0)
            
            # Create new user
            new_user = User(
                username=username,
                email=email,
                password_hash=hash_password(password)
            )
            db.add(new_user)
            db.commit()
            flash('Registration successful! Please login.', 'success')
            return redirect(url_for('login'))
        finally:
            db.close()
    
    return render_template('register.html', cart_count=0)


@app.route('/logout')
def logout():
    """User logout."""
    session.clear()
    flash('You have been logged out.', 'info')
    return redirect(url_for('index'))


@app.route('/')
def index():
    """Home page displaying all restaurants."""
    db = SessionLocal()
    try:
        restaurants = db.query(Restaurant).all()
        cart_count = get_cart_count()
        user = get_current_user()
        return render_template('index.html', restaurants=restaurants, cart_count=cart_count, user=user)
    finally:
        db.close()


@app.route('/restaurant/<int:restaurant_id>')
def restaurant(restaurant_id):
    """Display menu for a specific restaurant."""
    db = SessionLocal()
    try:
        restaurant = db.query(Restaurant).filter_by(id=restaurant_id).first()
        if not restaurant:
            flash('Restaurant not found.', 'error')
            return redirect(url_for('index'))
        
        menu_items = db.query(MenuItem).filter_by(restaurant_id=restaurant_id).all()
        cart_count = get_cart_count()
        return render_template('restaurant.html', restaurant=restaurant, menu_items=menu_items, cart_count=cart_count)
    finally:
        db.close()


@app.route('/cart/add', methods=['POST'])
def add_to_cart():
    """Add an item to the cart."""
    menu_item_id = request.form.get('menu_item_id')
    quantity = int(request.form.get('quantity', 1))
    
    # Validate quantity
    if quantity < 1:
        quantity = 1
    elif quantity > 20:
        quantity = 20
    
    db = SessionLocal()
    try:
        menu_item = db.query(MenuItem).filter_by(id=menu_item_id).first()
        
        if not menu_item:
            flash('Menu item not found.', 'error')
            return redirect(url_for('index'))
        
        # Check stock
        if not menu_item.is_in_stock:
            flash('This item is currently out of stock.', 'error')
            return redirect(url_for('restaurant', restaurant_id=menu_item.restaurant_id))
        
        if menu_item.stock_quantity < quantity:
            flash(f'Only {menu_item.stock_quantity} items available in stock.', 'warning')
            quantity = menu_item.stock_quantity
        
        # Get identifier (user_id if logged in, session_id if not)
        user_id = session.get('user_id') if 'user_id' in session else None
        session_id = get_session_id() if not user_id else None
        
        # Check if item already in cart
        query = db.query(CartItem).filter_by(menu_item_id=menu_item_id)
        if user_id:
            query = query.filter_by(user_id=user_id)
        else:
            query = query.filter_by(session_id=session_id)
        existing_item = query.first()
        
        # Deduct from stock
        menu_item.stock_quantity -= quantity
        
        if existing_item:
            existing_item.quantity += quantity
            if existing_item.quantity > 20:
                existing_item.quantity = 20
        else:
            cart_item = CartItem(
                session_id=session_id,
                user_id=user_id,
                menu_item_id=menu_item_id,
                quantity=quantity,
                unit_price=menu_item.price
            )
            db.add(cart_item)
        
        db.commit()
        flash(f'Added {menu_item.name} to cart!', 'success')
        return redirect(url_for('restaurant', restaurant_id=menu_item.restaurant_id))
    finally:
        db.close()


@app.route('/cart/update', methods=['POST'])
def update_cart():
    """Update the quantity of an item in the cart."""
    session_id = session.get('session_id')
    if not session_id:
        return redirect(url_for('index'))
    
    cart_item_id = request.form.get('cart_item_id')
    quantity = int(request.form.get('quantity', 0))
    
    db = SessionLocal()
    try:
        cart_item = db.query(CartItem).filter_by(id=cart_item_id, session_id=session_id).first()
        
        if not cart_item:
            flash('Cart item not found.', 'error')
            return redirect(url_for('cart'))
        
        if quantity <= 0:
            db.delete(cart_item)
            flash('Item removed from cart.', 'info')
        elif quantity > 20:
            cart_item.quantity = 20
            flash('Maximum quantity is 20.', 'warning')
        else:
            cart_item.quantity = quantity
            flash('Cart updated.', 'success')
        
        db.commit()
        return redirect(url_for('cart'))
    finally:
        db.close()


@app.route('/cart')
def cart():
    """Display the shopping cart."""
    db = SessionLocal()
    try:
        # Eagerly load menu_item relationship to avoid DetachedInstanceError
        from sqlalchemy.orm import joinedload
        
        # Check if user is logged in
        if 'user_id' in session:
            cart_items = db.query(CartItem).options(joinedload(CartItem.menu_item)).filter_by(user_id=session['user_id']).all()
        else:
            session_id = session.get('session_id')
            if not session_id:
                cart_items = []
            else:
                cart_items = db.query(CartItem).options(joinedload(CartItem.menu_item)).filter_by(session_id=session_id).all()
        
        subtotal = sum(item.subtotal for item in cart_items)
        subtotal = Decimal(str(subtotal))
        tax = Decimal('0.00')  # Placeholder for tax
        total = subtotal + tax
        
        cart_count = len(cart_items)
        user = get_current_user()
        return render_template('cart.html', cart_items=cart_items, subtotal=subtotal, tax=tax, total=total, cart_count=cart_count, user=user)
    finally:
        db.close()


@app.route('/checkout', methods=['POST'])
def checkout():
    """Process checkout by clearing the cart."""
    session_id = session.get('session_id')
    if not session_id:
        return redirect(url_for('index'))
    
    db = SessionLocal()
    try:
        cart_items = db.query(CartItem).filter_by(session_id=session_id).all()
        
        if not cart_items:
            flash('Your cart is empty.', 'warning')
            return redirect(url_for('cart'))
        
        # Clear cart by deleting all items
        for item in cart_items:
            db.delete(item)
        
        db.commit()
        flash('Order placed successfully!', 'success')
        return redirect(url_for('thank_you'))
    finally:
        db.close()


@app.route('/thank-you')
def thank_you():
    """Thank you page after checkout."""
    cart_count = 0
    return render_template('thank_you.html', cart_count=cart_count)


if __name__ == '__main__':
    port = int(os.getenv('PORT', 5000))
    app.run(debug=True, host='0.0.0.0', port=port)

