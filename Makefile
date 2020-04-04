.PHONY: clean All

All:
	@echo "----------Building project:[ evo - Release ]----------"
	@cd "evo" && "$(MAKE)" -f  "evo.mk"
clean:
	@echo "----------Cleaning project:[ evo - Release ]----------"
	@cd "evo" && "$(MAKE)" -f  "evo.mk" clean
