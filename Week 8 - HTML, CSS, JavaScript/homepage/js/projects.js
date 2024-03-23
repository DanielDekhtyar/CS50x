/*
* Code for the contact_me.html page
*/

/*
* Event listeners
*/
const backButton = document.getElementById('back-button');
backButton.addEventListener('click', backClick);

const hangmanImage = document.getElementById('hangman-pic');
hangmanImage.addEventListener('click', hangmanClick);

const enigmaImage = document.getElementById('enigma-pic');
enigmaImage.addEventListener('click', enigmaClick)

/*
* Functions for the event listeners
*/

// Go back to the main page
function backClick() {
    window.location.href = '../index.html';
}

// Open the GitHub repository for the Hangman game
function hangmanClick() {
    window.open('https://github.com/DanielDekhtyar/Hangman-with-Pygame')
}

// Open the GitHub repository for The Enigma Cipher
function enigmaClick() {
    window.open('https://github.com/DanielDekhtyar/The-Enigma-Cipher')
}