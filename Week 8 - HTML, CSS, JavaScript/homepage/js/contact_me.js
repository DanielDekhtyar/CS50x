/*
* Code for the contact_me.html page
*/

/*
* Event listeners
*/
const submitButton = document.getElementById('submit-button');
submitButton.addEventListener('click', submitClick);

const backButton = document.getElementById('back-button');
backButton.addEventListener('click', backClick);

/*
* Functions for the event listeners
*/

// Show the thank you message
function submitClick() {
    window.location.href = 'thankyou_for_contacting.html';
}

// Go back to the main page
function backClick() {
    window.location.href = '../index.html';
}