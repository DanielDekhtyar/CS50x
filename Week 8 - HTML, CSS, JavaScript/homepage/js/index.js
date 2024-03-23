/*
* Code for the index.html page
*/

/*
* Event listeners
*/
const hangmanImage = document.getElementById('hangman-pic');
hangmanImage.addEventListener('click', hangmanClick);

const enigmaImage = document.getElementById('enigma-pic');
enigmaImage.addEventListener('click', enigmaClick)

const LinkedIn = document.getElementById('LinkedIn');
LinkedIn.addEventListener('click', LinkedInClick);

// Open the GitHub repository for the Hangman game
function hangmanClick() {
    window.open('https://github.com/DanielDekhtyar/Hangman-with-Pygame')
}

// Open the GitHub repository for The Enigma Cipher
function enigmaClick() {
    window.open('https://github.com/DanielDekhtyar/The-Enigma-Cipher')
}

// Open my LinkedIn
function LinkedInClick() {
    window.open('https://www.linkedin.com/in/daniel-dekhtyar/')
}