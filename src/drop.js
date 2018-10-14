window.onload = function() {
	document.addEventListener("drop", function(e) {
		e.preventDefault();
		if (e.dataTransfer.items[0].type.startsWith("image"))
		{
			const blob = e.dataTransfer.items[0].getAsFile();
			const im = createImageBitmap(blob);
			im.then(function(imb) {
				const gl = document.getElementById("canvas").getContext("webgl2")
				gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, imb.width, imb.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, imb);
				gl.generateMipmap(gl.TEXTURE_2D);
			});
			im.catch(function() {console.log("Error loading image, try another one.")});
		}
		else
		{
			const reader = new FileReader();
			reader.onload = function(event) {
				const array = new Int8Array(event.target.result);
				Module.ccall("load_obj_from_js", "void", ["array", "number"], [array, array.length]);
			};
			const blob = e.dataTransfer.items[0].getAsFile();
			reader.readAsArrayBuffer(blob);
		}
		return false;
	});
	document.addEventListener("dragover", function(e) {
		e.preventDefault();
		return false;
	});
};