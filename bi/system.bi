/**
 * Execute a command.
 *
 *   - cmd: The command string.
 *
 * Return: the return code of the execution.
 */
function system(cmd:String) -> Integer32 {
  cpp{{
  return std::system(cmd_.c_str());
  }}
}

/**
 * Exit.
 *
 *   - code: An exit code.
 */
function exit(code:Integer) {
  cpp{{
  std::exit(code_);
  }}
}

/**
 * Make an object.
 *
 *   - name: Name of the class.
 *
 * Return: an optional with a value of the object if the make is successful,
 * or with no value otherwise.
 *
 * This is used to construct an object where the class is given in a string,
 * e.g. from user input. The class must not have constructor parameters.
 * Internally, it uses `dlsym()` to search the current process for a symbol
 * `make_name_` with C linkage, as generated by the Birch compiler for all
 * compatible types.
 */
function make(name:String) -> Object? {
  result:Object?;
  symbol:String <- "make_" + name + "_";
  cpp{{
  using make_t = bi::type::Object_*();
  void* addr = dlsym(RTLD_DEFAULT, symbol_.c_str());
  if (addr) {
    auto raw = reinterpret_cast<make_t*>(addr)();
    result_ = bi::SharedPointer<bi::type::Object_>(std::shared_ptr<bi::type::Object_>(raw));
  }
  }}
  return result;
}
