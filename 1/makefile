default:
	@echo "No targets specified."
%.cpp.out: %.cpp
	g++ -lglut -lGL -lGLU -g -o $@ $<
%.c.out: %.c
	gcc -lglut -lGL -lGLU -g -o $@ $< -lrt -lreadline
clean:
	rm -rf *.out
