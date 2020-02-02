/* application body */
let app = {
	dom: {},
	get_a() {
		let value = parseInt(app.dom.inputA.value, 10);

		/* accept only integer value */
		if(isNaN(value)) {
			value = 1;
		}

		/* check acceptable range */
		if(value < 1) {
			value = 1;
		}

		/* set the same value for `inputA` */
		app.dom.inputA.value = value;

		return value;
	},
	get_b() {
		let value = parseInt(app.dom.inputB.value, 10);

		/* accept only integer value */
		if(isNaN(value)) {
			value = 1;
		}

		/* check acceptable range */
		if(value < 1) {
			value = 1;
		}

		/* set the same value for `inputB` */
		app.dom.inputB.value = value;

		return value;
	},
	clear_output() {
		app.dom.output.innerHTML = "";
	},
	print(tab, ...text) {
		/* tab = 4 spaces */
		if(tab === true) {
			app.dom.output.innerHTML += '&nbsp;&nbsp;&nbsp;&nbsp;';
		}

		/* print content */
		for(let s of text) {
			app.dom.output.innerHTML += s;
		}

		app.dom.output.innerHTML += '<br>'; /* print new line */
	},
	gcd(a, b) {
		let c, step = 1;

		/* procedure: print b != 0 */
		const check_b = () => {
			app.print(false, step, ': ', b, ' &ne; 0 &rarr; ',
			  ((b !== 0) ? 'prawda' : 'fałsz'));
		};

		/* print GCD steps */
		app.print(false, 'a &larr; ', a);
		app.print(false, 'b &larr; ', b);
		app.print(false, '');
		check_b();

		while(b !== 0) {
			if(step > 1) check_b();

			app.print(true, 'c &larr; ', a, ' % ', b, ' = ', (a % b));
			c = a % b;

			app.print(true, 'a &larr; ', b);
			a = b;

			app.print(true, 'b &larr; ', c);
			b = c;

			app.print(false, '');
			step++;
		}

		check_b();
		app.print(true, 'wynik &larr; ', a);
	},
	clear_all() {
		app.clear_output();
		app.dom.inputA.value = "";
		app.dom.inputB.value = "";
	},
	main() {
		app.clear_output();
		app.gcd(app.get_a(), app.get_b());
	}
};

/* starting point */
document.addEventListener('DOMContentLoaded', () => {
	/* get elements from DOM */
	const $id = n => {return document.getElementById(n);};
	app.dom.inputA      = $id('inputA');
	app.dom.inputB      = $id('inputB');
	app.dom.buttonRun   = $id('buttonRun');
	app.dom.buttonClear = $id('buttonClear');
	app.dom.output      = $id('outputdiv');

	/* test for app.dom */
	for(let element in app.dom) {
		if(!app.dom[element]) {
			console.error(`Missing interface element: ${element}`);
			alert(`Missing interface element: ${element}`);
			return;
		}
	}

	/* callbacks */
	app.dom.inputA.addEventListener('change', app.get_a);
	app.dom.inputB.addEventListener('change', app.get_b);
	app.dom.buttonRun.addEventListener('click', app.main);
	app.dom.buttonClear.addEventListener('click', app.clear_all);
});