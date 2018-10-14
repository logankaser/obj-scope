window.onload = function() {
	document.addEventListener("drop", function(e) {
		e.preventDefault();
		const blob = e.dataTransfer.items[0].getAsFile();
		const im = createImageBitmap(blob);
		im.then(function(imb) {
			const gl = document.getElementById("canvas").getContext("webgl2")
			gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, imb.width, imb.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, imb);
			gl.generateMipmap(gl.TEXTURE_2D);
		});
		im.catch(function() {console.log("Error loading image, try another one.")});
		return false;
	});
	document.addEventListener("dragover", function(e) {
		e.preventDefault();
		return false;
	});
};