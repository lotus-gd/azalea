#ifndef UTILS_H
#define UTILS_H

#define ReCa reinterpret_cast

#define CREATE_HOOK(addr, func) \
if (MH_CreateHook(ReCa<void*>(addr), func##_h, ReCa<void**>(&func)) != MH_OK) return false;
#define CREATE_GD_HOOK(offset, func) CREATE_HOOK(gd::base + offset, func)

#define HOOK(type, ret, name, ...) \
inline ret(type* name)(__VA_ARGS__); \
ret type name##_h(__VA_ARGS__);
#define THISCALL_HOOK(ret, name, self, ...) \
inline ret(__thiscall* name)(self, __VA_ARGS__); \
ret __fastcall name##_h(self, void*, __VA_ARGS__);
#define THISCALL_HOOK_NO_ARGS(ret, name, self) \
inline ret(__thiscall* name)(self); \
ret __fastcall name##_h(self);

#endif // UTILS_H
