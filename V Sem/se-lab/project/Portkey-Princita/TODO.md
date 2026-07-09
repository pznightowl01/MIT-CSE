# TODO for Chatbot Accuracy and Response Cleanliness Improvements

- [ ] Enhance Intent Matching:
  - [ ] Expand regex patterns to capture more variations (synonyms, misspellings)
  - [ ] Add fuzzy string matching using difflib for better accuracy
  - [ ] Implement confidence scoring for intent matching
  - [ ] Add support for compound queries (multiple intents in one message)

- [ ] Improve Response Generation:
  - [ ] Make responses more concise and contextual
  - [ ] Implement response templates that adapt based on user context
  - [ ] Add progressive disclosure (show summary first, offer details on request)
  - [ ] Clean up formatting to avoid information overload

- [ ] Add New Intents and Patterns:
  - [ ] Create intents for common variations and edge cases
  - [ ] Add patterns for questions about delivery time, dietary restrictions, etc.
  - [ ] Implement intent chaining for follow-up questions

- [ ] Enhance Context Awareness:
  - [ ] Improve conversation memory to track user preferences
  - [ ] Add user state management (e.g., browsing restaurants, in cart flow)
  - [ ] Generate responses based on recent conversation history

- [ ] Response Formatting Improvements:
  - [ ] Use structured responses with clear sections
  - [ ] Implement response length limits with "read more" options
  - [ ] Add emoji and formatting strategically to keep it clean

- [ ] Update Dependencies:
  - [ ] Add difflib (built-in) for fuzzy matching
  - [ ] Update requirements.txt if needed

- [ ] Testing and Validation:
  - [ ] Update test files to validate new intents and responses
  - [ ] Test conversation flows to ensure cleanliness
  - [ ] Validate improved accuracy with various query variations
