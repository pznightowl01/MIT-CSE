"""SQLAlchemy models for Portkey food ordering app."""

from sqlalchemy import Column, Integer, String, Float, Boolean, ForeignKey, DECIMAL, DateTime
from sqlalchemy.orm import relationship, declarative_base
from datetime import datetime

# Create base class here to avoid circular imports
Base = declarative_base()


class User(Base):
    """User model for authentication."""
    
    __tablename__ = 'users'
    
    id = Column(Integer, primary_key=True)
    username = Column(String(50), unique=True, nullable=False)
    email = Column(String(100), unique=True, nullable=False)
    password_hash = Column(String(200), nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)
    
    # Relationship to cart items
    cart_items = relationship("CartItem", back_populates="user")
    
    def __repr__(self):
        return f"<User {self.username}>"


class Restaurant(Base):
    """Restaurant model representing a food establishment."""
    
    __tablename__ = 'restaurants'
    
    id = Column(Integer, primary_key=True)
    name = Column(String(100), nullable=False)
    address = Column(String(200), nullable=False)
    contact = Column(String(50), nullable=False)
    operating_hours = Column(String(100), nullable=False)  # e.g., "Mon-Sun: 10AM-10PM"
    cuisine_type = Column(String(50), nullable=False)  # e.g., "Italian", "Chinese"
    
    # Relationship to menu items
    menu_items = relationship("MenuItem", back_populates="restaurant", cascade="all, delete-orphan")
    
    def __repr__(self):
        return f"<Restaurant {self.name}>"


class MenuItem(Base):
    """Menu item model representing a food item available from a restaurant."""
    
    __tablename__ = 'menu_items'
    
    id = Column(Integer, primary_key=True)
    restaurant_id = Column(Integer, ForeignKey('restaurants.id'), nullable=False)
    name = Column(String(100), nullable=False)
    description = Column(String(500), nullable=False)
    price = Column(DECIMAL(10, 2), nullable=False)
    category = Column(String(50), nullable=False)  # e.g., "Appetizer", "Main", "Dessert", "Beverage"
    availability = Column(Boolean, default=True, nullable=False)
    stock_quantity = Column(Integer, default=100, nullable=False)  # Available stock
    
    # Relationship to restaurant
    restaurant = relationship("Restaurant", back_populates="menu_items")
    
    # Relationship to cart items
    cart_items = relationship("CartItem", back_populates="menu_item")
    
    @property
    def is_in_stock(self):
        """Check if item is in stock."""
        return self.stock_quantity > 0 and self.availability
    
    def __repr__(self):
        return f"<MenuItem {self.name}>"


class CartItem(Base):
    """Cart item model representing an item in the user's shopping cart."""
    
    __tablename__ = 'cart_items'
    
    id = Column(Integer, primary_key=True)
    session_id = Column(String(100), nullable=True, index=True)  # Anonymous session tracking
    user_id = Column(Integer, ForeignKey('users.id'), nullable=True)  # User ID for logged-in users
    menu_item_id = Column(Integer, ForeignKey('menu_items.id'), nullable=False)
    quantity = Column(Integer, nullable=False, default=1)
    unit_price = Column(DECIMAL(10, 2), nullable=False)
    
    # Relationships
    menu_item = relationship("MenuItem", back_populates="cart_items")
    user = relationship("User", back_populates="cart_items")
    
    @property
    def subtotal(self):
        """Calculate subtotal for this cart item."""
        return float(self.unit_price) * self.quantity
    
    def __repr__(self):
        return f"<CartItem {self.menu_item.name} x{self.quantity}>"
