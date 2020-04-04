.PHONY: clean All

All:
	@echo "----------Building project:[ evo - Debug ]----------"
	@cd "evo" && "$(MAKE)" -f  "evo.mk"
clean:
	@echo "----------Cleaning project:[ evo - Debug ]----------"
	@cd "evo" && "$(MAKE)" -f  "evo.mk" clean
