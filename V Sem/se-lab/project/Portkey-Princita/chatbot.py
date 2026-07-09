"""
Hedwig - Advanced ML-powered Chatbot for Portkey Food Delivery System
Handles restaurant queries, menu recommendations, order assistance, and customer support.
Enhanced with fuzzy matching, context awareness, and clean response generation.
"""

import re
import random
import time
import difflib
from datetime import datetime
from db import SessionLocal
from models import Restaurant, MenuItem

class Chatbot:
    """Hedwig chatbot for food delivery assistance with enhanced conversation capabilities."""

    def __init__(self):
        """Initialize chatbot with enhanced intents from provided dataset, database connection, and conversation memory."""
        # Provided dataset intents
        dataset = {
            "intents": [
                {"tag": "greeting",
                 "patterns": ["Hi", "Hey", "Hello", "Good morning!", "Hey! Good morning", "Hey there", "Hey Janet", "Very good morning", "A very good morning to you", "Greeting", "Greetings to you"],
                 "responses": ["Hello I'm Restrobot! How can I help you?", "Hi! I'm Restrobot. How may I assist you today?"]
                },
                {"tag": "book_table",
                 "patterns": ["Book a table","Can I book a table?", "I want to book a table", "Book seat", "I want to book a seat", "Can I book a seat?", "Could you help me book a table", "Can I reserve a seat?", "I need a reservation", "Can you help me with a reservation", "Can I book a reservation", "Can i have a table?", "Help me reserve a table", "book table"],
                 "responses": ["Sure, I'd be happy to help you book a table. How many people will be dining and what time would you prefer?"]
                },
                {"tag": "available_tables",
                 "patterns": ["How many seats are available?", "Available seats", "How many tables are available?", "Available tables", "Are there any tables available?", "What is the capacity of the restaurant", "Are there any available tables?", "Are there any seats left?", "I wanted to know if there are any tables available now", "May I know if you have any tables which I can book?"],
                 "responses": ["We have several tables available. Our restaurant can accommodate up to 50 people. What time are you looking for?"]
                },
                {"tag": "goodbye",
                 "patterns": ["cya", "I will leave now","See you later", "Goodbye", "Leaving now, Bye" , "Good bye dear", "Bye dear","I am Leaving", "Have a Good day", "cya later", "I gotta go now", "I gotta rush now", "Thank you, bye", "Bye", "Ok Bye", "Okay goodnight", "Have a good day ahead", "Have a great day", "Tata", "Take care"],
                 "responses": ["It's been my pleasure serving you!", "Hope to see you again soon! Goodbye!", "Bye! Hope to see you again!"]
                },
                {"tag": "identity",
                 "patterns": ["what is your name", "what should I call you", "whats your name?", "who are you", "Are you human?", "Am i talking to a bot", "Are you a bot", "Can i have your name please", "name"],
                 "responses": ["You can call me Restrobot.", "I'm Restrobot!", "I'm Restrobot."]
                },
                {"tag": "hours",
                 "patterns": ["when are you guys open", "what are your hours", "hours of operation", "hours", "what is the timing", "when are you open", "Are you open on all days?", "are you open now", "are you open on holidays", "are you guys open on all weekdays?", "working hours", "hours", "what are your working hours?"],
                 "responses": ["We are open 10am-12am Monday-Friday!"]
                },
                {"tag": "menu",
                 "patterns": ["Id like to order something", "whats on the menu", "could i get something to eat", "Im damn hungry", "I am hungry" ,"Show me the menu", "What food do you have", "wHat food are you offering?", "whats on the menu today?", "Let me see the menu", "menu"],
                 "responses": ["Let me show you our delicious menu options from various cuisines!"]
                },
                {"tag": "contact",
                 "patterns": ["contact information", "how do we contact you", "how can i contact you", "can i get the contact details", "I wanna give some feedback", "how can i give some feedback?", "CAn you give me the contact of an executive?", "What is the help desk phone number?","Can you give me your number", "Can i get the customer care number?", "CAn I get help desk number"],
                 "responses": ["You can contact us at contact@aindrisrestro.com, our help desk number is 8787878787"]
                },
                {"tag": "address",
                 "patterns": ["what is the location?","whats the location", "where are you located?", "where is the restaurant located?", "address", "whats the address?", "what is the address of the restaurant", "I am not able to locate you", "I cant find your location", "CAn i have the address of the restaurant", "how to reach there?", "Address?", "what is the address of this restaurant?"],
                 "responses": ["You can locate us at Aindri's Restro, Phase 1, Rd Number 6, Whitefield, Bengaluru, Karnataka 560066"]
                },
                {"tag": "positive_feedback",
                    "patterns": ["the noodles were amazing","i loved the food", "you did a good job", "Love the food", "Really love it", "Love the staff behavior", "my son devoured the brownie!", "pizza was so cheesy!", "perfectly baked", "we are very satisfied with the service", "the soup was a real game changer", "such delicious flavours", "so glad we discovered this place", "Me and my family is very satisfied with this service and food", "this place is awesome"],
                    "responses": ["Thank you for the positive feedback! We're glad you enjoyed your meal."]
                },
                {"tag": "negative_feedback",
                    "patterns": ["what the fuck is wrong with these noodles?", "The choco lava was so undercooked", "Ew such a waste of money man", "Prices are too high honestly", "I hate the menu, such less options", "too salty", "we were served cold food", "so disappointed", "the food is pathetic", "hate it", "my wife hates the food","eww", "hate the staff behavior", "i hate it", "hate the service","please train the staff properly", "This was such a waste of money", "Hate the staff", "Extremely dissatisfied", "disappointed", "so bad", "very bad", "disgusting food"],
                    "responses": ["I'm sorry to hear that. We appreciate your feedback and will work to improve."]
                },
                {"tag": "sanitation",
                    "patterns": ["is it really safe to eat here?","Could you tell your COVID safety protocols?", "I would like to know about the cleanliness of the restaurant", "Please share your sanitization process", "I am concerned about the COVID related sanitization", "Is it safe to eat out in this pandemic?", "are you clean", "i am concerned about the cleanliness"],
                    "responses": ["I understand your concern. Here are the WHO recommended COVID protocols we follow to ensure your safety: \n 1. All our staff are double masked 24x7. \n 2. All our staff is checked for fevers and other symptoms daily. \n 3. All surfaces are frequently sanitized. \n 4. We use this friendly bot to reduce physical closeness to the least!"]
                },
                {"tag": "offers",
                    "patterns": ["Could you tell me the pocket friendly options?","Are there any discounts going on?", "Are there any special offers today?", "What about the festive offers?", "Could you please tell me which foods are on discount?", "are there any discounts", "are there any discount offers", "do you have any offers?", "what are the offers going on?", "what are the discounts available?"],
                    "responses": ["We have great offers! Check our specials section for current discounts and deals."]
                },
                {"tag": "vegan_enquiry",
                    "patterns": ["Can I see the vegan option?","Do you have any vegan options??", "What is vegan in your menu?", "I am vegan.", "Do you also have vegan food?", "vegan", "is this restaurant vegan", "is this place vegan"],
                    "responses": ["Yes, we have several vegan options! Let me show you our vegan menu."]
                },
                {"tag": "veg_enquiry",
                    "patterns": ["Can I see the vegetarian options?","Do you have any vegetarian options??", "Please show me your best vegetarian foods", "I dont want to eat non veg", "I am vegetarian", "vegetarian", "is this place vegetarian?"],
                    "responses": ["We have an excellent selection of vegetarian dishes! Here's our vegetarian menu."]
                },
                {"tag": "recipe_enquiry",
                    "patterns": ["Could you tell me more about recipe of this dish?", "What is the recipe of this dish?", "what are the ingredients of this dish?", "tell me the recipe"],
                    "responses": ["I'd be happy to share some recipe details! What dish are you interested in?"]
                },
                {"tag": "suggest",
                    "patterns": ["what do you recommend?","do you have any suggestions","please suggest something","why don't you recommend me a dish", "help me choose what to order", "Surprise me!", "Do you have any special recommendations for me?", "What do you suggest?", "what is your suggestion", "what is a must try", "what should i try", "what should i eat?", "tell me what to order", "tell me what i should buy", "recommend me a dish", "suggest me a dish"],
                    "responses": ["I'd be happy to recommend some delicious options based on what you're craving!"]
                },
                {"tag": "general",
                    "patterns": ["okay","sure","cool","hmm", "fine", "thanks", "uhuh"],
                    "responses": [":)", "Glad to serve you!", "Happy to help!", "Always happy to assist you!"]
                }
            ]
        }

        # Convert dataset to intents dict
        self.intents = {}
        for intent in dataset["intents"]:
            tag = intent["tag"]
            patterns = [r'\b' + re.escape(p.lower()) + r'\b' for p in intent["patterns"]]  # Simple word boundaries
            responses = intent["responses"] if intent["responses"] else ["I'm here to help! How can I assist you?"]
            self.intents[tag] = {
                'patterns': patterns,
                'responses': responses,
                'concise': True  # Default to concise for new intents
            }

        # Add fallback if not present
        if 'fallback' not in self.intents:
            self.intents['fallback'] = {
                'patterns': [r'.*'],
                'responses': ["I'm not sure I understand. Could you please rephrase your question?"],
                'concise': True
            }

        # Enhanced conversation memory for context awareness
        self.conversation_memory = {}
        self.max_memory_items = 10  # Increased for better context
        self.fuzzy_threshold = 0.6  # Threshold for fuzzy matching

    def get_restaurants_info(self):
        """Get formatted list of restaurants from database."""
        try:
            db = SessionLocal()
            restaurants = db.query(Restaurant).all()
            db.close()

            if not restaurants:
                return "Sorry, no restaurants are currently available."

            response = "🏪 **Our Restaurants:**\n\n"
            for restaurant in restaurants:
                response += f"🍽️ **{restaurant.name}**\n"
                response += f"   📍 {restaurant.address}\n"
                response += f"   📞 {restaurant.contact}\n"
                response += f"   🕐 {restaurant.operating_hours}\n"
                response += f"   🍜 Cuisine: {restaurant.cuisine_type}\n\n"

            return response
        except Exception as e:
            return "Sorry, I'm having trouble accessing restaurant information right now. Please try again later."

    def get_menu_sample(self):
        """Get sample of popular menu items."""
        try:
            from sqlalchemy.orm import joinedload
            db = SessionLocal()
            # Get some popular items from different categories with restaurant info
            items = db.query(MenuItem).options(joinedload(MenuItem.restaurant)).filter(
                MenuItem.availability == True,
                MenuItem.stock_quantity > 0
            ).limit(8).all()
            db.close()

            if not items:
                return "Sorry, menu items are currently unavailable."

            response = "🍕 **Popular Menu Items:**\n\n"
            for item in items:
                price_inr = float(item.price) * 83.0  # Convert to INR
                response += f"🍽️ **{item.name}**\n"
                response += f"   📝 {item.description}\n"
                response += f"   💰 ₹{price_inr:.0f} ({item.category})\n"
                response += f"   🏪 {item.restaurant.name}\n\n"

            return response
        except Exception as e:
            return "Sorry, I'm having trouble accessing menu information right now."

    def get_recommendations(self):
        """Get food recommendations."""
        recommendations = [
            "🍛 Try the Butter Chicken from Dollops - it's absolutely delicious!",
            "🍜 The Hakka Noodles from Dollops are a customer favorite!",
            "🍕 Margherita Pizza from Hadiqa is perfect for pizza lovers!",
            "🐟 Don't miss the Mangalore Fish Curry from Machali - authentic coastal cuisine!",
            "🍗 Chicken Ghee Roast from Madhuvan's is a must-try Mangalorean specialty!",
            "🥘 For vegetarian options, try the Masala Dosa from Pai Tiffins!",
            "🍰 Gulab Jamun from Dollops makes a perfect dessert!",
            "☕ Filter Coffee from Pai Tiffins is the best way to end your meal!"
        ]
        return random.choice(recommendations) + "\n\nBrowse our restaurants to see the full menu! 🏪"

    def match_intent(self, message):
        """Enhanced intent matching using regex patterns and fuzzy matching."""
        message = message.lower().strip()

        # First try exact regex matching
        for intent_name, intent_data in self.intents.items():
            for pattern in intent_data['patterns']:
                if re.search(pattern, message, re.IGNORECASE):
                    return intent_name, intent_data

        # If no exact match, try fuzzy matching on key phrases
        best_match = self.fuzzy_intent_match(message)
        if best_match:
            return best_match

        return 'fallback', self.intents['fallback']

    def fuzzy_intent_match(self, message):
        """Use fuzzy string matching to find the best intent match."""
        best_score = 0
        best_intent = None

        # Define key phrases for each intent for fuzzy matching
        intent_keywords = {
            'greetings': ['hello', 'hi', 'hey', 'good morning', 'good afternoon', 'good evening', 'howdy', 'whats up', 'sup', 'yo', 'hola', 'ciao', 'namaste', 'welcome', 'start'],
            'restaurant_query': ['restaurant', 'restaurants', 'places to eat', 'where to eat', 'eatery', 'diner', 'food places', 'eating places', 'show restaurants', 'list restaurants'],
            'menu_query': ['menu', 'food', 'dish', 'what to eat', 'what do you have', 'what can i order', 'show menu', 'see menu', 'food options', 'dish options'],
            'recommendation': ['recommend', 'suggest', 'best', 'favorite', 'popular', 'what should i try', 'what should i order', 'help me choose', 'good food', 'amazing food'],
            'payment_info': ['payment', 'pay', 'how to pay', 'payment method', 'card', 'upi', 'wallet', 'net banking', 'razorpay', 'secure payment'],
            'order_help': ['order', 'ordering', 'how to order', 'place order', 'make order', 'cart', 'add to cart', 'buy food', 'deliver food'],
            'location_query': ['location', 'where', 'address', 'area', 'place', 'manipal', 'mangalore', 'delivery area', 'service area', 'restaurant location'],
            'hours_query': ['hours', 'time', 'open', 'close', 'when', 'timing', 'schedule', 'operating hours', 'open now', 'restaurant hours'],
            'feedback': ['feedback', 'review', 'rate', 'rating', 'comment', 'complaint', 'issue', 'problem', 'suggestion', 'support', 'contact'],
            'specials': ['special', 'specials', 'deal', 'offer', 'discount', 'promotion', 'cheap', 'budget', 'affordable', 'save money', 'combo'],
            'goodbye': ['bye', 'goodbye', 'see you', 'thank', 'thanks', 'appreciate', 'exit', 'quit', 'later', 'take care', 'farewell']
        }

        for intent_name, keywords in intent_keywords.items():
            for keyword in keywords:
                # Calculate similarity score
                score = difflib.SequenceMatcher(None, message, keyword).ratio()
                if score > best_score and score >= self.fuzzy_threshold:
                    best_score = score
                    best_intent = intent_name

        if best_intent:
            return best_intent, self.intents[best_intent]

        return None

    def get_response(self, user_message, user_id=None):
        """Generate response based on user message with context awareness."""
        try:
            # Clean and normalize message
            user_message = user_message.strip()
            if not user_message:
                return {
                    'response': "I didn't receive any message. How can I help you with food ordering today? 🦉",
                    'intent': 'empty_message',
                    'success': True
                }

            # Match intent
            intent, intent_data = self.match_intent(user_message)

            # Get base response
            response = random.choice(intent_data['responses'])

            # Add context-aware elements
            response = self.add_context_awareness(response, intent, user_id)

            # Add specific information based on intent and concise flag
            if not intent_data.get('concise', False):
                if intent == 'restaurant_query':
                    # Check if follow_up is disabled for this intent
                    if intent_data.get('follow_up', True):
                        response += "\n\n" + self.get_restaurants_info()
                    else:
                        # Provide a concise response without overwhelming details
                        response += "\n\nWe have 10 amazing restaurants across Manipal and Mangalore! You can browse them on our homepage or ask me about specific cuisines. 🏪"

                elif intent == 'menu_query':
                    response += "\n\n" + self.get_menu_sample()

                elif intent == 'recommendation':
                    response += "\n\n" + self.get_recommendations()
            else:
                # For concise intents, add minimal additional information
                if intent == 'order_help':
                    response += "\n\n💡 Quick tip: Browse → Add to Cart → Checkout → Pay securely!"

                elif intent == 'payment_info':
                    response += "\n\n💳 Secure payments via Razorpay - cards, UPI, wallets, net banking!"

                elif intent == 'location_query':
                    response += "\n\n📍 We serve Manipal and Mangalore with amazing restaurants!"

                elif intent == 'hours_query':
                    response += "\n\n🕐 Most restaurants open 11 AM - 11 PM. Check individual pages for exact timings!"

                elif intent == 'feedback':
                    response += "\n\n📧 Contact us at support@portkey.com - we value your feedback!"

                elif intent == 'specials':
                    response += "\n\n🎯 Check restaurant pages for current deals and specials!"

            # Update conversation memory
            self.update_conversation_memory(user_id, intent, user_message)

            # Return as JSON for API
            return {
                'response': response,
                'intent': intent,
                'success': True
            }

        except Exception as e:
            print(f"Chatbot error: {str(e)}")  # For debugging
            return {
                'response': "Sorry, I'm experiencing some technical difficulties. Please try again in a moment! 🦉",
                'intent': 'error',
                'success': False,
                'error': str(e)
            }

    def add_context_awareness(self, response, intent, user_id):
        """Add context-aware elements to responses."""
        if not user_id:
            return response

        # Get recent conversation context
        recent_intents = self.get_recent_intents(user_id, 3)

        # Add follow-up suggestions based on context
        if intent == 'greetings' and 'restaurant_query' in recent_intents:
            response += " I remember you were looking at restaurants earlier. Would you like me to show them again?"
        elif intent == 'menu_query' and 'recommendation' in recent_intents:
            response += " Since you asked for recommendations before, I can also show you our full menu!"
        elif intent == 'order_help' and 'payment_info' in recent_intents:
            response += " I see you were asking about payments. The ordering process is simple and secure!"

        return response

    def update_conversation_memory(self, user_id, intent, message):
        """Update conversation memory for context awareness."""
        if not user_id:
            return

        if user_id not in self.conversation_memory:
            self.conversation_memory[user_id] = []

        # Add new interaction
        self.conversation_memory[user_id].append({
            'intent': intent,
            'message': message[:100],  # Truncate long messages
            'timestamp': datetime.now()
        })

        # Keep only recent interactions
        if len(self.conversation_memory[user_id]) > self.max_memory_items:
            self.conversation_memory[user_id] = self.conversation_memory[user_id][-self.max_memory_items:]

    def get_recent_intents(self, user_id, count=3):
        """Get recent intents from conversation memory."""
        if user_id not in self.conversation_memory:
            return []

        recent = self.conversation_memory[user_id][-count:]
        return [item['intent'] for item in recent]

# Create global chatbot instance
chatbot = Chatbot()
