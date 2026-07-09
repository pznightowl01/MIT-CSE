# Portkey Food Ordering App - Quick Setup

## Prerequisites
- Python 3.8 or higher
- pip (Python package manager)

## Setup Steps

### 1. Create Virtual Environment (Recommended)
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
python setup.py
```

Or alternatively:
```bash
python -c "from db import init_db, seed_db; init_db(); seed_db()"
```

### 4. Run the Application
```bash
flask --app app.py run
```

The app will be available at: `http://localhost:5000`

## Project Structure

```
portkey/
├── app.py                      # Main Flask application
├── models.py                   # SQLAlchemy database models
├── db.py                       # Database configuration and seeding
├── setup.py                    # Setup script
├── requirements.txt            # Python dependencies
├── README.md                   # Documentation
├── .gitignore                  # Git ignore rules
├── templates/                  # Jinja2 templates
│   ├── base.html              # Base template with navigation
│   ├── index.html             # Restaurant listing page
│   ├── restaurant.html        # Menu view page
│   ├── cart.html              # Shopping cart page
│   └── thank_you.html         # Order confirmation page
└── static/                     # Static files
    └── style.css              # Custom styles (optional)
```

## Features Implemented

✅ Browse 5 restaurants (Italian, Chinese, Indian, Mexican, American)
✅ View menus with 8-12 items per restaurant
✅ Add items to cart with quantity selection (1-20)
✅ Update/remove cart items
✅ Real-time cart totals
✅ Checkout simulation (no payments)
✅ Thank you page with order confirmation
✅ Responsive UI with Tailwind CSS
✅ Server-side session management
✅ SQLite database with SQLAlchemy ORM

## API Routes

- `GET /` - Home page (list restaurants)
- `GET /restaurant/<id>` - Restaurant menu page
- `POST /cart/add` - Add item to cart
- `POST /cart/update` - Update cart item quantity
- `GET /cart` - View shopping cart
- `POST /checkout` - Process checkout (clear cart)
- `GET /thank-you` - Order confirmation page

## Usage

1. **Browse Restaurants**: Click on "View Menu" for any restaurant
2. **Add to Cart**: Select quantity and click "Add to Cart"
3. **Manage Cart**: View cart, update quantities, or remove items
4. **Checkout**: Click "Proceed to Checkout" to simulate order
5. **Confirmation**: See thank you page

## Technical Details

- **Backend**: Flask with server-side sessions
- **Database**: SQLite with SQLAlchemy ORM
- **Frontend**: Jinja2 templates with Tailwind CSS CDN
- **Session**: Anonymous user tracking via Flask session IDs
- **Port**: 5000 (configurable via .env)

## Troubleshooting

If you encounter any issues:

1. Make sure all dependencies are installed: `pip install -r requirements.txt`
2. Ensure the database is initialized: `python setup.py`
3. Check that port 5000 is available
4. Clear browser cookies if session issues occur

## Notes

- No user authentication required
- No payment processing
- No order persistence (cart clears after checkout)
- No admin dashboard
- No delivery tracking
- No ML chatbot

This is a minimal MVP for demonstration purposes.

