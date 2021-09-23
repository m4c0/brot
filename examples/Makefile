# Just an example of what can be done

oscillator.brot: oscillator.bom.brot oscillator.comp.brot oscillator.net.brot
	cat $? | ../build/brot-expand > oscillator.brot
	cat oscillator.brot | ../build/brot-cat

clean:
	rm oscillator.brot
