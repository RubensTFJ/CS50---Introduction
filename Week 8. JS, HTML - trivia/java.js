document.addEventListener('DOMContentLoaded', function(){
	let right_button = document.querySelector("#correct");
	let wrong_buttons = document.querySelectorAll(".incorrect");
	let p1_message = document.querySelector("#p1_message");
	let text_button = document.querySelector("#text_answear");
	let p2_message = document.querySelector("#p2_message");
	let input;

	right_button.addEventListener('click', function(){
		p1_message.innerHTML = "Correct!";
		single_selection(right_button, "green");
	})

	for (let i = 0; i < wrong_buttons.length; i++)
	{
		wrong_buttons[i].addEventListener('click', function(){
			p1_message.innerHTML = "Incorrect.";
			single_selection(wrong_buttons[i], "red");
		})
	}

	text_button.addEventListener('click', function() {
		input = document.querySelector("input");
		if (input.value.toLowerCase() === "yes"){
			input.style.color = "green";
			p2_message.innerHTML = "Correct!";
		}
		else {
			input.style.color = "red";
			p2_message.innerHTML = "Incorrect.";
		}
	})
});

function single_selection(button, color) {
	let change;

	if (button.style.backgroundColor == color)
	{
		change = '#d9edff';
		p1_message.innerHTML = "";
	}
	else
		change = color;
	reset_colors(".incorrect");
	reset_colors("#correct");
	button.style.backgroundColor = change;
}

function reset_colors(class_var) {
	let elements;

    if (class_var.startsWith("#")) {
        elements = [document.querySelector(class_var)];
    }
	else
        elements = document.querySelectorAll(class_var);
	for (let i = 0; i < elements.length; i++)
		elements[i].style.backgroundColor = '#d9edff';
}
