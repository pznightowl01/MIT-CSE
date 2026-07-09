"""Database configuration and initialization for Portkey app."""

import os
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from models import Base, Restaurant, MenuItem, CartItem, User

# Database configuration
DATABASE_URL = "sqlite:///database.db"
engine = create_engine(DATABASE_URL, echo=False)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)


def init_db():
    """Initialize database by creating all tables."""
    from models import Restaurant, MenuItem, CartItem, User
    Base.metadata.drop_all(bind=engine)
    Base.metadata.create_all(bind=engine)
    print("Database initialized successfully!")


def seed_db():
    """Seed the database with sample restaurant and menu data."""
    session = SessionLocal()
    
    try:
        # Check if data already exists
        if session.query(Restaurant).count() > 0:
            print("Database already seeded. Skipping seed process.")
            return
        
        # Restaurant 1: Italian
        italian = Restaurant(
            name="Mama Rosa's Italian Kitchen",
            address="123 Main Street, Downtown",
            contact="(555) 123-4567",
            operating_hours="Mon-Sun: 11AM-10PM",
            cuisine_type="Italian"
        )
        session.add(italian)
        session.flush()
        
        session.add_all([
            MenuItem(restaurant_id=italian.id, name="Margherita Pizza", description="Classic pizza with fresh mozzarella, tomato sauce, and basil", price=14.99, category="Main", availability=True, stock_quantity=50),
            MenuItem(restaurant_id=italian.id, name="Spaghetti Carbonara", description="Creamy pasta with bacon, egg, and parmesan", price=16.99, category="Main", availability=True, stock_quantity=40),
            MenuItem(restaurant_id=italian.id, name="Caesar Salad", description="Romaine lettuce, croutons, parmesan, caesar dressing", price=9.99, category="Appetizer", availability=True, stock_quantity=30),
            MenuItem(restaurant_id=italian.id, name="Chicken Parmesan", description="Breaded chicken breast with marinara and melted mozzarella", price=18.99, category="Main", availability=True, stock_quantity=35),
            MenuItem(restaurant_id=italian.id, name="Garlic Bread", description="Fresh baked bread with garlic butter", price=6.99, category="Appetizer", availability=True, stock_quantity=60),
            MenuItem(restaurant_id=italian.id, name="Tiramisu", description="Coffee-soaked ladyfingers with mascarpone cream", price=8.99, category="Dessert", availability=True, stock_quantity=25),
            MenuItem(restaurant_id=italian.id, name="Panna Cotta", description="Italian custard with raspberry sauce", price=7.99, category="Dessert", availability=True, stock_quantity=20),
            MenuItem(restaurant_id=italian.id, name="House Wine", description="Red or white wine by the glass", price=8.99, category="Beverage", availability=True, stock_quantity=100),
            MenuItem(restaurant_id=italian.id, name="Limoncello", description="Italian lemon liqueur", price=6.99, category="Beverage", availability=False, stock_quantity=0),
        ])
        
        # Restaurant 2: Chinese
        chinese = Restaurant(
            name="Golden Dragon",
            address="456 Oak Avenue, Midtown",
            contact="(555) 234-5678",
            operating_hours="Mon-Sun: 12PM-11PM",
            cuisine_type="Chinese"
        )
        session.add(chinese)
        session.flush()
        
        session.add_all([
            MenuItem(restaurant_id=chinese.id, name="Kung Pao Chicken", description="Spicy stir-fried chicken with peanuts and vegetables", price=15.99, category="Main", availability=True, stock_quantity=45),
            MenuItem(restaurant_id=chinese.id, name="Sweet and Sour Pork", description="Crispy pork in tangy sweet and sour sauce", price=14.99, category="Main", availability=True, stock_quantity=40),
            MenuItem(restaurant_id=chinese.id, name="Spring Rolls", description="Crispy vegetable spring rolls with dipping sauce", price=6.99, category="Appetizer", availability=True, stock_quantity=55),
            MenuItem(restaurant_id=chinese.id, name="Beef Lo Mein", description="Stir-fried noodles with beef and vegetables", price=13.99, category="Main", availability=True, stock_quantity=38),
            MenuItem(restaurant_id=chinese.id, name="Hot and Sour Soup", description="Traditional spicy and tangy soup", price=5.99, category="Appetizer", availability=True, stock_quantity=60),
            MenuItem(restaurant_id=chinese.id, name="Mapo Tofu", description="Spicy Sichuan tofu with ground pork", price=12.99, category="Main", availability=True, stock_quantity=30),
            MenuItem(restaurant_id=chinese.id, name="Mango Pudding", description="Fresh mango pudding", price=6.99, category="Dessert", availability=True, stock_quantity=20),
            MenuItem(restaurant_id=chinese.id, name="Egg Tart", description="Flaky pastry with custard filling", price=4.99, category="Dessert", availability=True, stock_quantity=25),
            MenuItem(restaurant_id=chinese.id, name="Jasmine Tea", description="Hot or iced jasmine tea", price=3.99, category="Beverage", availability=True, stock_quantity=150),
            MenuItem(restaurant_id=chinese.id, name="Bubble Tea", description="Tapioca pearls with milk tea", price=5.99, category="Beverage", availability=True, stock_quantity=80),
        ])
        
        # Restaurant 3: Indian
        indian = Restaurant(
            name="Spice Garden",
            address="789 Elm Street, Uptown",
            contact="(555) 345-6789",
            operating_hours="Tue-Sun: 11AM-9PM",
            cuisine_type="Indian"
        )
        session.add(indian)
        session.flush()
        
        session.add_all([
            MenuItem(restaurant_id=indian.id, name="Chicken Tikka Masala", description="Creamy tomato-based curry with grilled chicken", price=17.99, category="Main", availability=True, stock_quantity=42),
            MenuItem(restaurant_id=indian.id, name="Butter Chicken", description="Tender chicken in rich buttery tomato sauce", price=17.99, category="Main", availability=True, stock_quantity=38),
            MenuItem(restaurant_id=indian.id, name="Samosas", description="Crispy pastry filled with spiced potatoes", price=5.99, category="Appetizer", availability=True, stock_quantity=70),
            MenuItem(restaurant_id=indian.id, name="Tandoori Lamb", description="Marinated lamb cooked in clay oven", price=19.99, category="Main", availability=True, stock_quantity=25),
            MenuItem(restaurant_id=indian.id, name="Vegetable Biryani", description="Fragrant basmati rice with mixed vegetables", price=14.99, category="Main", availability=True, stock_quantity=32),
            MenuItem(restaurant_id=indian.id, name="Naan Bread", description="Fresh baked flatbread with garlic butter", price=4.99, category="Appetizer", availability=True, stock_quantity=90),
            MenuItem(restaurant_id=indian.id, name="Gulab Jamun", description="Sweet milk dumplings in rose syrup", price=6.99, category="Dessert", availability=True, stock_quantity=22),
            MenuItem(restaurant_id=indian.id, name="Mango Lassi", description="Yogurt drink with fresh mango", price=5.99, category="Beverage", availability=True, stock_quantity=120),
            MenuItem(restaurant_id=indian.id, name="Chai Tea", description="Spiced Indian tea", price=3.99, category="Beverage", availability=True, stock_quantity=150),
        ])
        
        # Restaurant 4: Mexican
        mexican = Restaurant(
            name="El Fuego Cantina",
            address="321 Pine Street, Central District",
            contact="(555) 456-7890",
            operating_hours="Mon-Sat: 11AM-10PM, Sun: 12PM-8PM",
            cuisine_type="Mexican"
        )
        session.add(mexican)
        session.flush()
        
        session.add_all([
            MenuItem(restaurant_id=mexican.id, name="Beef Tacos", description="Three soft tacos with seasoned beef, lettuce, cheese, and salsa", price=12.99, category="Main", availability=True, stock_quantity=48),
            MenuItem(restaurant_id=mexican.id, name="Chicken Enchiladas", description="Corn tortillas stuffed with chicken, topped with cheese and sauce", price=15.99, category="Main", availability=True, stock_quantity=35),
            MenuItem(restaurant_id=mexican.id, name="Guacamole and Chips", description="Fresh avocado dip with crispy tortilla chips", price=8.99, category="Appetizer", availability=True, stock_quantity=40),
            MenuItem(restaurant_id=mexican.id, name="Chile Relleno", description="Roasted poblano pepper stuffed with cheese", price=13.99, category="Main", availability=True, stock_quantity=28),
            MenuItem(restaurant_id=mexican.id, name="Carnitas Burrito", description="Slow-cooked pork with beans, rice, and cheese", price=14.99, category="Main", availability=True, stock_quantity=30),
            MenuItem(restaurant_id=mexican.id, name="Quesadilla", description="Cheese quesadilla with choice of chicken or vegetables", price=10.99, category="Main", availability=True, stock_quantity=45),
            MenuItem(restaurant_id=mexican.id, name="Flan", description="Caramel custard dessert", price=7.99, category="Dessert", availability=True, stock_quantity=18),
            MenuItem(restaurant_id=mexican.id, name="Churros", description="Fried dough pastries with cinnamon and sugar", price=6.99, category="Dessert", availability=True, stock_quantity=24),
            MenuItem(restaurant_id=mexican.id, name="Horchata", description="Rice and cinnamon drink", price=4.99, category="Beverage", availability=True, stock_quantity=100),
            MenuItem(restaurant_id=mexican.id, name="Jarritos Soda", description="Mexican fruit soda", price=3.99, category="Beverage", availability=True, stock_quantity=200),
        ])
        
        # Restaurant 5: American
        american = Restaurant(
            name="Classic American Diner",
            address="555 Broadway, Westside",
            contact="(555) 567-8901",
            operating_hours="Mon-Sun: 7AM-10PM",
            cuisine_type="American"
        )
        session.add(american)
        session.flush()
        
        session.add_all([
            MenuItem(restaurant_id=american.id, name="Classic Burger", description="Beef patty with lettuce, tomato, pickles, and special sauce", price=11.99, category="Main", availability=True, stock_quantity=55),
            MenuItem(restaurant_id=american.id, name="BBQ Pulled Pork Sandwich", description="Slow-cooked pork with tangy BBQ sauce and coleslaw", price=13.99, category="Main", availability=True, stock_quantity=40),
            MenuItem(restaurant_id=american.id, name="Buffalo Wings", description="Crispy chicken wings with buffalo sauce and blue cheese", price=12.99, category="Appetizer", availability=True, stock_quantity=35),
            MenuItem(restaurant_id=american.id, name="Mac and Cheese", description="Creamy macaroni with three types of cheese", price=10.99, category="Main", availability=True, stock_quantity=50),
            MenuItem(restaurant_id=american.id, name="Caesar Salad", description="Crisp romaine with parmesan and croutons", price=9.99, category="Appetizer", availability=True, stock_quantity=30),
            MenuItem(restaurant_id=american.id, name="Fish and Chips", description="Beer-battered cod with fries", price=15.99, category="Main", availability=True, stock_quantity=28),
            MenuItem(restaurant_id=american.id, name="Apple Pie", description="Homemade apple pie with vanilla ice cream", price=7.99, category="Dessert", availability=True, stock_quantity=20),
            MenuItem(restaurant_id=american.id, name="Chocolate Milkshake", description="Rich chocolate shake topped with whipped cream", price=6.99, category="Beverage", availability=True, stock_quantity=80),
            MenuItem(restaurant_id=american.id, name="Root Beer Float", description="Classic root beer with vanilla ice cream", price=6.99, category="Beverage", availability=True, stock_quantity=90),
            MenuItem(restaurant_id=american.id, name="Lemonade", description="Fresh squeezed lemonade", price=4.99, category="Beverage", availability=True, stock_quantity=110),
        ])
        
        session.commit()
        print(f"Successfully seeded database with {session.query(Restaurant).count()} restaurants and {session.query(MenuItem).count()} menu items!")
        
    except Exception as e:
        session.rollback()
        print(f"Error seeding database: {e}")
        raise
    finally:
        session.close()


if __name__ == "__main__":
    init_db()
    seed_db()

