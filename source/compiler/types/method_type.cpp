
#include <vector>
#include <memory>
#include "method_type.hpp"

MethodType::MethodType(const std::vector<ArgEntry>& args, const SharedPtr<Type>& return_type)
  : Type(Type::TypeID::MethodTy), args(args), return_type(return_type) {}

const std::vector<ArgEntry>& MethodType::GetArgs() const {
  return args;
}

void MethodType::AddArg(const ArgEntry& arg_entry) {
  args.push_back(arg_entry);
}

SharedPtr<Type> MethodType::GetReturnType() const {
  return return_type;
}

int MethodType::GetArgsNum() const {
  return args.size();
}

MethodType::MethodType() : Type(Type::TypeID::MethodTy) {}

std::string MethodType::ToString() const {
  std::string res;
  res += return_type->ToString() + " (";
  for (const ArgEntry& entry : args) {
    res += entry.type->ToString() + " " + entry.symbol.name + ", ";
  }
  res += ")";
  return res;
}
