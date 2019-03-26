fixScale(document);

main();

function main() {
    var val = document.getElementById('rgbValue');
    var hVal = document.getElementById('hslaValue');

    colorjoe.registerExtra('text', function(p, joe, o) {
        e(p, o.text? o.text: 'text');
    });

    function e(parent, text) {
        var elem = document.createElement('div');
        elem.innerHTML = text;
        parent.appendChild(elem);
    }

    colorjoe.rgb('rgbPicker').on('change', function(c) {
        val.innerHTML = c.css();
		console.log(Math.round(c.red()*255)+';'+Math.round(c.green()*255)+';'+Math.round(c.blue()*255));
		
		const Http = new XMLHttpRequest();
		const url='http://192.168.1.139:8080/api/color/'+Math.round(c.red()*255)+';'+Math.round(c.green()*255)+';'+Math.round(c.blue()*255);
		Http.open("GET", url);
		Http.send();
		Http.onreadystatechange=(e)=>{
			console.log(Http.responseText)
		}
			
		
    }).update();

    colorjoe.rgb('extraPicker', '#113c38', [
                 'close',
                 'currentColor',
                 ['fields', {space: 'RGB', limit: 255, fix: 2}],
                 'hex',
                 'text',
                 ['text', {text: 'param demo'}]
    ]);

    colorjoe.hsl('hslPicker', '#113c38', [
                 'alpha',
                 'currentColor',
                 ['fields', {space: 'HSLA', limit: 100}],
                 ['fields', {space: 'CMYKA', limit: 100}],
                 'hex'
    ]).on('change', function(c) {
        hVal.innerHTML = 'Alpha: ' + c.alpha().toFixed(2);
    }).update();

    var cj = colorjoe.rgb('closeablePicker', 'red', [
                          'close',
                          'currentColor'
    ]);

    document.getElementById('showPicker').onclick = function(e) {
        e.preventDefault();

        cj.show();
    };
}
