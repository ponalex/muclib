#flags : -fsanitize=leak

test: 
	gcc -fsanitize=leak -o my_test my_list.c listlibrary/my_list.c
