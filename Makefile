
init:
	$(eval ORIGIN_ENTER=$(shell readelf $(FILE) -h |grep "Entry point address:" |awk '{print $$4}'))
	$(eval ARCH=$(readelf $(FILE) -h |grep "Class" |awk '{print $$2}'))
	cd x64 && NEW_ENTER=$(NEW_ENTER) ORIGIN_ENTER=$(ORIGIN_ENTER) make
	python3 ./tool-chain/foo.py ./x64/inject.bin $(FILE) ./a.out
	$(eval NEW_ENTER=$(shell readelf a.out -l |grep LOAD | awk 'END{print}' |awk '{print $$3}'))
	./tool-chain/cep ./a.out $(NEW_ENTER) ./b.out

clean:
	-rm -r ./x64/*.bin
	-rm -r ./x64/*.o
	-rm -r ./x64/*.asm
	-rm -r ./x86/*.bin
	-rm -r ./x86/*.o
	-rm -r ./x86/*.asm
