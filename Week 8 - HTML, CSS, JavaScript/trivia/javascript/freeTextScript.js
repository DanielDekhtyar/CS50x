/*
* Code for check if the answers is correct or not and displaying feedback on the screen
*/

// Add an event listener to the button when the DOM content is loaded
document.addEventListener('DOMContentLoaded', function() {
// get the elements of the multiple choice buttons
const button = document.getElementsByClassName('button');

// Add a click event listener to each button
for (let i = 0; i < button.length; i++) {
    // will not work if the button is the check button from the free text section
    if (button[i].id !== 'check-button') {
        button[i].addEventListener('click', multiChoiceClick);
    }
}

// Select the free text submit button element by its ID
const freeResponseButton = document.getElementById('check-button');

// Add a click event listener to the free text button
freeResponseButton.addEventListener('click', freeResponseClick);
});


function multiChoiceClick(event) {
    event.preventDefault();

    // Get the id of the button that was clicked
    const buttonId = event.target.id;

    // Emu photo that will be displayed in case of a correct answer
    const photo = document.getElementById('emu-photo');
    // Correct answer text
    const correctText = document.getElementById('multiple-choice-answer-correct');
    // Wrong answer text
    const wrongText = document.getElementById('multiple-choice-answer-wrong');

    if (buttonId === 'emu-war'){
        correctText.style.visibility = 'visible';
        correctText.style.paddingTop = '30px';

        wrongText.style.visibility = 'hidden';

        photo.style.visibility = 'visible';
        photo.style.height = '620px'
        photo.style.width = '930px';
    } else{
        correctText.style.visibility = 'hidden';
        wrongText.style.visibility = 'visible';
        photo.style.visibility = 'hidden';
        photo.style.height = '0px';
        photo.style.width = '0px';
    }
}


// Define a function that will be called when the button is clicked
function freeResponseClick(event) {
    event.preventDefault();

    // Get the text from the input box
    let inputText = document.getElementById('input-box').value;
    inputText = inputText.toLowerCase();

    // Walt Disney and Mickey Mouse photo
    const photo = document.getElementById('disney');

    // Text shown when the answer is correct
    const correctText = document.getElementById('free-response-answer-correct');

    // Text shown when the answer is wrong
    const wrongText = document.getElementById('free-response-answer-wrong');

    if (inputText === 'mouse' || inputText === 'mouses' || inputText === 'mice') {
        photo.style.visibility = 'visible';
        photo.style.height = '650px';
        photo.style.width = '650px';

        wrongText.style.visibility = 'hidden';

        correctText.style.visibility = 'visible';
        correctText.style.paddingTop = '30px';

    } else {
        correctText.style.visibility = 'hidden';

        wrongText.style.visibility = 'visible';
        wrongText.style.padding = '0px'

        photo.style.visibility = 'hidden';
        photo.style.height = '0px';
        photo.style.width = '0px';
    }
}
