# Just an example of what can be done

oscillator.jlcpcb.bom: oscillator.brot
	cat $? | ../build/brot-jlcpcb-bom > $@

oscillator.brot: oscillator.bom.brot oscillator.comp.brot oscillator.net.brot
	cat $? | ../build/brot-expand | ../build/brot-cat > $@

clean:
	rm oscillator.brot oscillator.jlcpcb.bom
