# SERVICE
style:
	find ./MVCModel -name "*.h" -o -name "*.cc" | xargs clang-format --style=google -n

gost:
	find ./MVCModel -name "*.h" -o -name "*.cc" | xargs clang-format --style=google -i
