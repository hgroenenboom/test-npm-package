console.log("inside preload.js");

var npmpackage = require("@hgroenenboom/npmpackage/build/Release/npmpackage");

function displayMessage(message) {
    console.log(message);
	document.getElementById("console").innerHTML = message + "<br /> ";
}

window.addEventListener('DOMContentLoaded', () => {
	npmpackage.registerLengthCallback((length)=>{
		displayMessage(length)
	});

	document.getElementById("count").addEventListener('input', (e)=>{ 
		npmpackage.length(e.target.value);
	});
});
