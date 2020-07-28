debug: format check build
	@cd slides.d && ../dyvo

build:
	@gcc -o dyvo -Wall *.c -lmd4c -lcairo

check:
	@cppcheck --suppress=missingIncludeSystem --template=gcc \
	          --quiet --platform=unix64 --enable=all *.c

format:
	@astyle --formatted --project *.c *.h

graph:
	@cinclude2dot | xdot -

