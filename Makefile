QCompile : 
	cmake -S . -B build && cmake --build ./build

Rebuild :
	@if [ -d ./build ]; then \
		printf "Rebuilding...\n"; \
		rm -rf ./build; \
		cmake -S . -B build && cmake --build build; \
		printf "Done!\n"; \
	else \
		printf "Build directory does not exist!\n"; \
		cmake -S . -B build && cmake --build build; \
	fi
