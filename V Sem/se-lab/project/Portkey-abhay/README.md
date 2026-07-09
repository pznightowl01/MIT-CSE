# Portkey Food Ordering App

A minimal food ordering web application built with Flask, SQLite, and Jinja2 templates.

## Features

- User authentication with login and registration
- Browse restaurants by cuisine type
- View detailed menus with categories and live stock quantities
- Add items to cart with quantity management (stock-aware)
- Update or remove cart items
- View cart with real-time totals
- Real-time inventory tracking (stock decreases as items are added)
- Simulate checkout (no payments)
- Clean, modern, responsive UI

## Setup Instructions

### 1. Create Virtual Environment

```bash
# Windows
python -m venv .venv
.venv\Scripts\activate

# macOS/Linux
python -m venv .venv
source .venv/bin/activate
```

### 2. Install Dependencies

```bash
pip install -r requirements.txt
```

### 3. Initialize Database

```bash
python -c "from db import init_db, seed_db; init_db(); seed_db()"
```

This creates the SQLite database and seeds it with 5 restaurants and their menu items.

### 4. Run the Application

```bash
flask --app app.py run
```

Or specify a custom port:

```bash
flask --app app.py run --port 5000
```

The application will run on `http://localhost:5000`

## Project Structure

```
portkey/
├── app.py                 # Flask application and routes
├── models.py              # SQLAlchemy models
├── db.py                  # Database initialization and seeding
├── requirements.txt       # Python dependencies
├── .env                   # Environment variables
├── database.db            # SQLite database (created on first run)
├── templates/             # Jinja2 templates
│   ├── base.html
│   ├── index.html
│   ├── restaurant.html
│   ├── cart.html
│   └── thank_you.html
└── static/               # Static files
    └── style.css
```

## Usage

1. **Register/Login**: Create an account or login with existing credentials
2. **Browse Restaurants**: Visit the home page to see all available restaurants
3. **View Menu**: Click "View Menu" on any restaurant card
4. **Add to Cart**: Select quantity (limited by stock) and click "Add to Cart"
   - Stock quantities are visible on each menu item
   - Stock decreases as items are added to cart
5. **Manage Cart**: View cart, update quantities, or remove items
6. **Checkout**: Complete order simulation (cart clears automatically)
7. **Confirmation**: See thank you page with order confirmation

### Guest vs Logged-in Users

- **Guests**: Can browse and add items to cart (session-based)
- **Logged-in users**: Can access persistent cart across devices

## Technical Details

- **Backend**: Flask with server-side sessions
- **Database**: SQLite with SQLAlchemy ORM
- **Frontend**: Jinja2 templates with Tailwind CSS
- **Session**: Anonymous user tracking via Flask sessions
- **Port**: Default 5000 (configurable via .env)

## Out of Scope

This MVP explicitly excludes:
- User authentication
- Payment processing
- Order history
- Delivery tracking
- Admin dashboard
- ML chatbot
- Real-time notifications

