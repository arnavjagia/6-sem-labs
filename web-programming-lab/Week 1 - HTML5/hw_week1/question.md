Design a conference registration form with the following fields and requirements:

1. Participant Details:
    - Full Name: Required, text input with a placeholder "Enter your full name."
    - Email: Required, validates format, placeholder "example@domain.com."
    - Phone Number: Required, 10-digit input.
    - Age: Number input, only accepts values between 18 and 60.

2. Event Preferences:
    - Dropdown to select up to two events: Options: Coding Contest, Hackathon, Paper Presentation, Robotics Challenge, Keynote Session. Use the multiple attribute to allow multi-selection.
    - Add a note below the dropdown: "Hold Ctrl (Windows) or Command (Mac) to select multiple options."

3. Accommodation Details:
    - A group of radio buttons to select accommodation type: Options: "Hostel," "Hotel," "None" (required).

4. Dietary Preferences:
    - A group of checkboxes to allow multiple dietary preferences: Options: "Vegetarian," "Non-Vegetarian," "Vegan," "Other (Specify below)."
    - Include a text input below for specifying "Other" dietary preferences (disabled by default and enabled only when "Other" is checked).

5. Additional Info:
    - Upload Documents: A file input for uploading student ID (PDF only, maximum size 5 MB). Use the accept attribute.
    - Comments/Requests: A textarea for participants to write comments (optional, with a character limit of 300).

6. Consent and Submission:
    - A checkbox to confirm the participant agrees to the terms and conditions (required).
    - Include two buttons:
        - "Submit" button to send data to the server (Display in the next page the results using either “get” or “post”).
        - "Reset" button to clear all fields.