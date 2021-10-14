# Just an example of what can be done

all: oscillator.jlcpcb.bom oscillator.jlcpcb.pnp oscillator.gerber.drh

oscillator.gerber.drl: oscillator.drill.brot
	cat $? | ../build/brot-gerber-drill > $@

oscillator.jlcpcb.bom: oscillator.brot
	cat $? | ../build/brot-jlcpcb-bom > $@

oscillator.jlcpcb.pnp: oscillator.brot
	cat $? | ../build/brot-jlcpcb-pnp > $@

oscillator.brot: oscillator.bom.brot oscillator.comp.brot oscillator.net.brot
	cat $? | ../build/brot-expand | ../build/brot-cat > $@

clean:
	rm -f oscillator.brot 
	rm -f oscillator.gerber.drl 
	rm -f oscillator.jlcpcb.bom
	rm -f oscillator.jlcpcb.pnp
