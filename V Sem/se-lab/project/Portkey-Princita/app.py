"""
Enhanced Flask application for Portkey food ordering app.
Includes simplified payment system and ML chatbot integration.
"""

import os
import hashlib
import hmac
import json
from decimal import Decimal
from flask import Flask, render_template, request, redirect, url_for, session, flash, jsonify
from dotenv import load_dotenv
from db import SessionLocal
from models import Restaurant, MenuItem, CartItem, User, Order, OrderItem, Feedback, DeliveryFeedback
from chatbot import chatbot
from functools import wraps

# Load environment variables
load_dotenv()

# Initialize Flask app
app = Flask(__name__)
app.config['SECRET_KEY'] = os.getenv('SECRET_KEY', os.urandom(24))
app.config['SESSION_TYPE'] = 'filesystem'

# Currency conversion rate (USD to INR)
USD_TO_INR = 83.0

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
    """Calculate the total for the current user's cart in INR."""
    session_id = session.get('session_id')
    if not session_id:
        return Decimal('0.00')
    db = SessionLocal()
    try:
        cart_items = db.query(CartItem).filter_by(session_id=session_id).all()
        total = sum(item.subtotal for item in cart_items)
        # Convert to INR
        total_inr = Decimal(str(total)) * Decimal(str(USD_TO_INR))
        return total_inr
    finally:
        db.close()

def convert_to_inr(usd_amount):
    """Convert USD to INR."""
    return float(usd_amount) * USD_TO_INR

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
            existing_user = db.query(User).filter(
                (User.username == username) | (User.email == email)
            ).first()
            
            if existing_user:
                flash('Username or email already exists.', 'error')
                return render_template('register.html', cart_count=0)
            
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

        # Get current cart items for button logic
        if 'user_id' in session:
            cart_items = db.query(CartItem).filter_by(user_id=session['user_id']).all()
        else:
            session_id = session.get('session_id')
            if session_id:
                cart_items = db.query(CartItem).filter_by(session_id=session_id).all()
            else:
                cart_items = []
        cart_item_ids = {item.menu_item_id for item in cart_items}

        # Convert prices to INR for display
        for item in menu_items:
            item.price_inr = convert_to_inr(item.price)
            item.in_cart = item.id in cart_item_ids

        return render_template('restaurant.html', restaurant=restaurant, menu_items=menu_items, cart_count=cart_count)
    finally:
        db.close()

@app.route('/cart/add', methods=['POST'])
def add_to_cart():
    """Add or remove an item from the cart (toggle functionality)."""
    menu_item_id = request.form.get('menu_item_id')

    db = SessionLocal()
    try:
        menu_item = db.query(MenuItem).filter_by(id=menu_item_id).first()
        if not menu_item:
            flash('Menu item not found.', 'error')
            return redirect(url_for('index'))

        if not menu_item.is_in_stock:
            flash('This item is currently out of stock.', 'error')
            return redirect(url_for('restaurant', restaurant_id=menu_item.restaurant_id))

        user_id = session.get('user_id') if 'user_id' in session else None
        session_id = get_session_id() if not user_id else None

        query = db.query(CartItem).filter_by(menu_item_id=menu_item_id)
        if user_id:
            query = query.filter_by(user_id=user_id)
        else:
            query = query.filter_by(session_id=session_id)

        existing_item = query.first()

        if existing_item:
            # Remove item from cart
            menu_item.stock_quantity += existing_item.quantity  # Restore stock
            db.delete(existing_item)
            db.commit()
            flash(f'Removed {menu_item.name} from cart!', 'info')
        else:
            # Add item to cart (quantity=1)
            if menu_item.stock_quantity < 1:
                flash(f'Only {menu_item.stock_quantity} items available in stock.', 'warning')
                return redirect(url_for('restaurant', restaurant_id=menu_item.restaurant_id))

            menu_item.stock_quantity -= 1  # Deduct stock

            cart_item = CartItem(
                session_id=session_id,
                user_id=user_id,
                menu_item_id=menu_item_id,
                quantity=1,
                unit_price=menu_item.price
            )
            db.add(cart_item)
            db.commit()
            flash(f'Added {menu_item.name} to cart!', 'success')

        return redirect(url_for('restaurant', restaurant_id=menu_item.restaurant_id))
    finally:
        db.close()

@app.route('/cart')
def cart():
    """Display the shopping cart."""
    db = SessionLocal()
    try:
        from sqlalchemy.orm import joinedload
        
        if 'user_id' in session:
            cart_items = db.query(CartItem).options(joinedload(CartItem.menu_item)).filter_by(user_id=session['user_id']).all()
        else:
            session_id = session.get('session_id')
            if not session_id:
                cart_items = []
            else:
                cart_items = db.query(CartItem).options(joinedload(CartItem.menu_item)).filter_by(session_id=session_id).all()
        
        subtotal = sum(item.subtotal for item in cart_items)
        subtotal_usd = Decimal(str(subtotal))
        subtotal_inr = subtotal_usd * Decimal(str(USD_TO_INR))
        
        tax = Decimal('0.00')
        total_inr = subtotal_inr + tax
        
        # Add INR prices to cart items for display
        for item in cart_items:
            item.unit_price_inr = convert_to_inr(item.unit_price)
            item.subtotal_inr = convert_to_inr(item.subtotal)
        
        cart_count = len(cart_items)
        user = get_current_user()
        
        return render_template('cart.html', cart_items=cart_items, 
                             subtotal=subtotal_inr, tax=tax, total=total_inr, 
                             cart_count=cart_count, user=user, currency='INR')
    finally:
        db.close()

@app.route('/process-payment', methods=['POST'])
def process_payment():
    """Process simplified payment and create order."""
    payment_method = request.form.get('payment_method', 'Simplified Payment')

    session_id = session.get('session_id')
    user_id = session.get('user_id')

    if not session_id and not user_id:
        flash('Session expired. Please try again.', 'error')
        return redirect(url_for('cart'))

    db = SessionLocal()
    try:
        # Get cart items
        if user_id:
            cart_items = db.query(CartItem).filter_by(user_id=user_id).all()
        else:
            cart_items = db.query(CartItem).filter_by(session_id=session_id).all()

        if not cart_items:
            flash('Cart is empty.', 'error')
            return redirect(url_for('cart'))

        # Calculate total
        total_inr = sum(item.subtotal for item in cart_items)
        total_inr = Decimal(str(total_inr)) * Decimal(str(USD_TO_INR))

        # Create order
        order = Order(
            user_id=user_id,
            total_amount=total_inr,
            status='confirmed',
            payment_id=f'{payment_method.lower().replace(" ", "_")}_{hashlib.md5(str(total_inr).encode()).hexdigest()[:10]}'
        )
        db.add(order)
        db.flush()  # Get order ID

        # Create order items
        for cart_item in cart_items:
            order_item = OrderItem(
                order_id=order.id,
                menu_item_id=cart_item.menu_item_id,
                quantity=cart_item.quantity,
                unit_price=cart_item.unit_price,
                subtotal=Decimal(str(cart_item.subtotal))
            )
            db.add(order_item)

        # Clear cart
        for item in cart_items:
            db.delete(item)

        db.commit()

        # Store order ID in session for thank you page
        session['last_order_id'] = order.id

        flash(f'Payment successful via {payment_method}! Your order has been placed.', 'success')
        return redirect(url_for('thank_you'))
    finally:
        db.close()





@app.route('/thank-you')
def thank_you():
    """Thank you page after successful payment."""
    cart_count = 0
    order_id = session.get('last_order_id')
    order = None

    if order_id:
        db = SessionLocal()
        try:
            order = db.query(Order).filter_by(id=order_id).first()
        finally:
            db.close()

    return render_template('thank_you.html', cart_count=cart_count, order=order)

# Chatbot API endpoints
@app.route('/api/chatbot', methods=['POST'])
def chatbot_endpoint():
    """Chatbot API endpoint with enhanced error handling and user context."""
    try:
        data = request.get_json()
        if not data:
            return jsonify({'error': 'Invalid JSON data'}), 400

        user_message = data.get('message', '').strip()
        if not user_message:
            return jsonify({
                'response': "I didn't receive any message. How can I help you with food ordering today? 🦉",
                'intent': 'empty_message',
                'success': True
            })

        # Get user context for conversation memory
        user_id = session.get('user_id') or session.get('session_id')

        response = chatbot.get_response(user_message, user_id)
        return jsonify(response)

    except Exception as e:
        print(f"Chatbot API error: {str(e)}")  # For debugging
        return jsonify({
            'response': "I'm experiencing some technical difficulties. Please try again in a moment! 🦉",
            'intent': 'error',
            'success': False,
            'error': str(e)
        }), 500

@app.route('/chatbot-page')
def chatbot_page():
    """Chatbot interface page."""
    cart_count = get_cart_count()
    user = get_current_user()
    return render_template('chatbot.html', cart_count=cart_count, user=user)

@app.route('/profile')
@login_required
def profile():
    """User profile page with order history."""
    db = SessionLocal()
    try:
        user = get_current_user()
        orders = db.query(Order).filter_by(user_id=user.id).order_by(Order.created_at.desc()).all()
        cart_count = get_cart_count()
        return render_template('profile.html', user=user, orders=orders, cart_count=cart_count)
    finally:
        db.close()

@app.route('/order/<int:order_id>')
@login_required
def order_details(order_id):
    """Display detailed order information."""
    db = SessionLocal()
    try:
        user = get_current_user()
        order = db.query(Order).filter_by(id=order_id, user_id=user.id).first()

        if not order:
            flash('Order not found.', 'error')
            return redirect(url_for('profile'))

        cart_count = get_cart_count()
        return render_template('order_details.html', order=order, cart_count=cart_count, user=user)
    finally:
        db.close()

@app.route('/feedback/<int:order_id>', methods=['GET', 'POST'])
@login_required
def submit_feedback(order_id):
    """Submit feedback for a completed order."""
    db = SessionLocal()
    try:
        user = get_current_user()
        order = db.query(Order).filter_by(id=order_id, user_id=user.id).first()

        if not order:
            flash('Order not found.', 'error')
            return redirect(url_for('profile'))

        # Check if feedback already exists
        existing_feedback = db.query(Feedback).filter_by(order_id=order_id).first()
        if existing_feedback:
            flash('Feedback already submitted for this order.', 'info')
            return redirect(url_for('order_details', order_id=order_id))

        if request.method == 'POST':
            rating = int(request.form.get('rating', 5))
            comment = request.form.get('comment', '').strip()

            feedback = Feedback(
                order_id=order_id,
                user_id=user.id,
                rating=rating,
                comment=comment if comment else None
            )
            db.add(feedback)
            db.commit()

            flash('Thank you for your feedback!', 'success')
            return redirect(url_for('order_details', order_id=order_id))

        cart_count = get_cart_count()
        return render_template('feedback_form.html', order=order, cart_count=cart_count, user=user)
    finally:
        db.close()

@app.route('/settings', methods=['GET', 'POST'])
@login_required
def settings():
    """User account settings page."""
    user = get_current_user()
    cart_count = get_cart_count()

    if request.method == 'POST':
        action = request.form.get('action')

        if action == 'change_password':
            current_password = request.form.get('current_password')
            new_password = request.form.get('new_password')
            confirm_password = request.form.get('confirm_password')

            if not current_password or not new_password or not confirm_password:
                flash('All password fields are required.', 'error')
            elif new_password != confirm_password:
                flash('New passwords do not match.', 'error')
            elif hash_password(current_password) != user.password_hash:
                flash('Current password is incorrect.', 'error')
            else:
                db = SessionLocal()
                try:
                    user.password_hash = hash_password(new_password)
                    db.commit()
                    flash('Password changed successfully!', 'success')
                finally:
                    db.close()

        elif action == 'update_preferences':
            # Handle preference updates (theme, notifications, etc.)
            flash('Preferences updated successfully!', 'success')

    return render_template('settings.html', user=user, cart_count=cart_count)

@app.route('/delete-account', methods=['POST'])
@login_required
def delete_account():
    """Delete user account."""
    user = get_current_user()
    confirm_username = request.form.get('confirm_username')

    if confirm_username != user.username:
        flash('Username confirmation does not match.', 'error')
        return redirect(url_for('settings'))

    db = SessionLocal()
    try:
        # Delete user (cascade will handle related records)
        db.delete(user)
        db.commit()

        # Clear session
        session.clear()
        flash('Account deleted successfully.', 'info')
        return redirect(url_for('index'))
    finally:
        db.close()

# API endpoints for order management
@app.route('/api/orders')
@login_required
def get_orders_api():
    """API endpoint to get user's orders."""
    db = SessionLocal()
    try:
        user = get_current_user()
        orders = db.query(Order).filter_by(user_id=user.id).order_by(Order.created_at.desc()).all()
        return jsonify([order.to_dict() for order in orders])
    finally:
        db.close()

@app.route('/api/feedback', methods=['POST'])
@login_required
def submit_feedback_api():
    """API endpoint to submit feedback."""
    try:
        data = request.get_json()
        order_id = data.get('order_id')
        rating = data.get('rating')
        comment = data.get('comment')

        if not order_id or not rating:
            return jsonify({'error': 'Order ID and rating are required'}), 400

        db = SessionLocal()
        try:
            user = get_current_user()
            order = db.query(Order).filter_by(id=order_id, user_id=user.id).first()

            if not order:
                return jsonify({'error': 'Order not found'}), 404

            # Check if feedback already exists
            existing_feedback = db.query(Feedback).filter_by(order_id=order_id).first()
            if existing_feedback:
                return jsonify({'error': 'Feedback already submitted'}), 400

            feedback = Feedback(
                order_id=order_id,
                user_id=user.id,
                rating=rating,
                comment=comment
            )
            db.add(feedback)
            db.commit()

            return jsonify({'message': 'Feedback submitted successfully', 'feedback': feedback.to_dict()})
        finally:
            db.close()
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    port = int(os.getenv('PORT', 5000))
    app.run(debug=True, host='0.0.0.0', port=port)
