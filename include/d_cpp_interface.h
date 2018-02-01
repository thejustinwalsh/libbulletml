#define D_CPP_CLASS(CLASS, CLASS_NAME) ;

#define D_CPP_NEW_0(CLASS, NEW_NAME) \
CLASS* NEW_NAME() { \
  return new CLASS(); \
}

#define D_CPP_NEW_1(CLASS, NEW_NAME, ARG1) \
CLASS* NEW_NAME(ARG1 arg1) { \
  return new CLASS(arg1); \
}

#define D_CPP_NEW_2(CLASS, NEW_NAME, ARG1, ARG2) \
CLASS* NEW_NAME(ARG1 arg1, ARG2 arg2) { \
  return new CLASS(arg1, arg2); \
}

#define D_CPP_NEW_3(CLASS, NEW_NAME, ARG1, ARG2, ARG3) \
CLASS* NEW_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3) { \
  return new CLASS(arg1, arg2, arg3); \
}

#define D_CPP_NEW_4(CLASS, NEW_NAME, ARG1, ARG2, ARG3, ARG4) \
CLASS* NEW_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4) { \
  return new CLASS(arg1, arg2, arg3, arg4); \
}

#define D_CPP_NEW_5(CLASS, NEW_NAME, ARG1, ARG2, ARG3, ARG4, ARG5) \
CLASS* NEW_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5) { \
  return new CLASS(arg1, arg2, arg3, arg4, arg5); \
}

#define D_CPP_NEW_6(CLASS, NEW_NAME, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) \
CLASS* NEW_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6) { \
  return new CLASS(arg1, arg2, arg3, arg4, arg5, arg6); \
}

#define D_CPP_NEW_7(CLASS, NEW_NAME, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) \
CLASS* NEW_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7) { \
  return new CLASS(arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
}

#define D_CPP_NEW_8(CLASS, NEW_NAME, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8) \
CLASS* NEW_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7, ARG8 arg8) { \
  return new CLASS(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
}

#define D_CPP_NEW_9(CLASS, NEW_NAME, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9) \
CLASS* NEW_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7, ARG8 arg8, ARG9 arg9) { \
  return new CLASS(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
}

#define D_CPP_DELETE(CLASS, DELETE_NAME) \
void DELETE_NAME(CLASS* c) { delete c; } 

#define D_CPP_METHOD_0(CLASS, METHOD, METHOD_NAME, RETURN) \
RETURN METHOD_NAME(CLASS* c) { \
  return c->METHOD(); \
}

#define D_CPP_METHOD_1(CLASS, METHOD, METHOD_NAME, RETURN, ARG1) \
RETURN METHOD_NAME(CLASS* c, ARG1 arg1) { \
  return c->METHOD(arg1); \
}

#define D_CPP_METHOD_2(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2) \
RETURN METHOD_NAME(CLASS* c, ARG1 arg1, ARG2 arg2) { \
  return c->METHOD(arg1, arg2); \
}

#define D_CPP_METHOD_3(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3) \
RETURN METHOD_NAME(CLASS* c, ARG1 arg1, ARG2 arg2, ARG3 arg3) { \
  return c->METHOD(arg1, arg2, arg3); \
}

#define D_CPP_METHOD_4(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4) \
RETURN METHOD_NAME(CLASS* c, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4) { \
  return c->METHOD(arg1, arg2, arg3, arg4); \
}

#define D_CPP_METHOD_5(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5) \
RETURN METHOD_NAME(CLASS* c, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5) { \
  return c->METHOD(arg1, arg2, arg3, arg4, arg5); \
}

#define D_CPP_METHOD_6(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) \
RETURN METHOD_NAME(CLASS* c, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6) { \
  return c->METHOD(arg1, arg2, arg3, arg4, arg5, arg6); \
}

#define D_CPP_METHOD_7(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) \
RETURN METHOD_NAME(CLASS* c, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7) { \
  return c->METHOD(arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
}

#define D_CPP_METHOD_8(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8) \
RETURN METHOD_NAME(CLASS* c, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7, ARG8 arg8) { \
  return c->METHOD(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
}

#define D_CPP_METHOD_9(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9) \
RETURN METHOD_NAME(CLASS* c, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7, ARG8 arg8, ARG9 arg9) { \
  return c->METHOD(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
}

#define D_CPP_STATIC_METHOD_0(CLASS, METHOD, METHOD_NAME, RETURN) \
RETURN METHOD_NAME() { \
  return CLASS::METHOD(); \
}

#define D_CPP_STATIC_METHOD_1(CLASS, METHOD, METHOD_NAME, RETURN, ARG1) \
RETURN METHOD_NAME(ARG1 arg1) { \
  return CLASS::METHOD(arg1); \
}

#define D_CPP_STATIC_METHOD_2(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2) \
RETURN METHOD_NAME(ARG1 arg1, ARG2 arg2) { \
  return CLASS::METHOD(arg1, arg2); \
}

#define D_CPP_STATIC_METHOD_3(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3) \
RETURN METHOD_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3) { \
  return CLASS::METHOD(arg1, arg2, arg3); \
}

#define D_CPP_STATIC_METHOD_4(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4) \
RETURN METHOD_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4) { \
  return CLASS::METHOD(arg1, arg2, arg3, arg4); \
}

#define D_CPP_STATIC_METHOD_5(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5) \
RETURN METHOD_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5) { \
  return CLASS::METHOD(arg1, arg2, arg3, arg4, arg5); \
}

#define D_CPP_STATIC_METHOD_6(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) \
RETURN METHOD_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6) { \
  return CLASS::METHOD(arg1, arg2, arg3, arg4, arg5, arg6); \
}

#define D_CPP_STATIC_METHOD_7(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) \
RETURN METHOD_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7) { \
  return CLASS::METHOD(arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
}

#define D_CPP_STATIC_METHOD_8(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8) \
RETURN METHOD_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7, ARG8 arg8) { \
  return CLASS::METHOD(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
}

#define D_CPP_STATIC_METHOD_9(CLASS, METHOD, METHOD_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9) \
RETURN METHOD_NAME(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7, ARG8 arg8, ARG9 arg9) { \
  return CLASS::METHOD(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
}

#define D_CPP_BASE_CLASS_OPEN(BASE, BASE_NAME) \
struct BASE_NAME : public BASE { 
#define D_CPP_VIRTUAL_METHOD_0(CLASS, METHOD, RETURN) \
  virtual RETURN METHOD() { \
    return D_##METHOD##_fp(this ); \
  } \
  void D_set_##METHOD(RETURN (*fp) (CLASS* )) { \
    D_##METHOD##_fp = fp; \
  } \
  RETURN (*D_##METHOD##_fp) (CLASS*); 

#define D_CPP_VIRTUAL_METHOD_1(CLASS, METHOD, RETURN, ARG1) \
  virtual RETURN METHOD(ARG1 arg1) { \
    return D_##METHOD##_fp(this , arg1); \
  } \
  void D_set_##METHOD(RETURN (*fp) (CLASS* , ARG1)) { \
    D_##METHOD##_fp = fp; \
  } \
  RETURN (*D_##METHOD##_fp) (CLASS*, ARG1); 

#define D_CPP_VIRTUAL_METHOD_2(CLASS, METHOD, RETURN, ARG1, ARG2) \
  virtual RETURN METHOD(ARG1 arg1, ARG2 arg2) { \
    return D_##METHOD##_fp(this , arg1, arg2); \
  } \
  void D_set_##METHOD(RETURN (*fp) (CLASS* , ARG1, ARG2)) { \
    D_##METHOD##_fp = fp; \
  } \
  RETURN (*D_##METHOD##_fp) (CLASS*, ARG1, ARG2); 

#define D_CPP_VIRTUAL_METHOD_3(CLASS, METHOD, RETURN, ARG1, ARG2, ARG3) \
  virtual RETURN METHOD(ARG1 arg1, ARG2 arg2, ARG3 arg3) { \
    return D_##METHOD##_fp(this , arg1, arg2, arg3); \
  } \
  void D_set_##METHOD(RETURN (*fp) (CLASS* , ARG1, ARG2, ARG3)) { \
    D_##METHOD##_fp = fp; \
  } \
  RETURN (*D_##METHOD##_fp) (CLASS*, ARG1, ARG2, ARG3); 

#define D_CPP_VIRTUAL_METHOD_4(CLASS, METHOD, RETURN, ARG1, ARG2, ARG3, ARG4) \
  virtual RETURN METHOD(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4) { \
    return D_##METHOD##_fp(this , arg1, arg2, arg3, arg4); \
  } \
  void D_set_##METHOD(RETURN (*fp) (CLASS* , ARG1, ARG2, ARG3, ARG4)) { \
    D_##METHOD##_fp = fp; \
  } \
  RETURN (*D_##METHOD##_fp) (CLASS*, ARG1, ARG2, ARG3, ARG4); 

#define D_CPP_VIRTUAL_METHOD_5(CLASS, METHOD, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5) \
  virtual RETURN METHOD(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5) { \
    return D_##METHOD##_fp(this , arg1, arg2, arg3, arg4, arg5); \
  } \
  void D_set_##METHOD(RETURN (*fp) (CLASS* , ARG1, ARG2, ARG3, ARG4, ARG5)) { \
    D_##METHOD##_fp = fp; \
  } \
  RETURN (*D_##METHOD##_fp) (CLASS*, ARG1, ARG2, ARG3, ARG4, ARG5); 

#define D_CPP_VIRTUAL_METHOD_6(CLASS, METHOD, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) \
  virtual RETURN METHOD(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6) { \
    return D_##METHOD##_fp(this , arg1, arg2, arg3, arg4, arg5, arg6); \
  } \
  void D_set_##METHOD(RETURN (*fp) (CLASS* , ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)) { \
    D_##METHOD##_fp = fp; \
  } \
  RETURN (*D_##METHOD##_fp) (CLASS*, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6); 

#define D_CPP_VIRTUAL_METHOD_7(CLASS, METHOD, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) \
  virtual RETURN METHOD(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7) { \
    return D_##METHOD##_fp(this , arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
  } \
  void D_set_##METHOD(RETURN (*fp) (CLASS* , ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7)) { \
    D_##METHOD##_fp = fp; \
  } \
  RETURN (*D_##METHOD##_fp) (CLASS*, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7); 

#define D_CPP_VIRTUAL_METHOD_8(CLASS, METHOD, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8) \
  virtual RETURN METHOD(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7, ARG8 arg8) { \
    return D_##METHOD##_fp(this , arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
  } \
  void D_set_##METHOD(RETURN (*fp) (CLASS* , ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8)) { \
    D_##METHOD##_fp = fp; \
  } \
  RETURN (*D_##METHOD##_fp) (CLASS*, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8); 

#define D_CPP_VIRTUAL_METHOD_9(CLASS, METHOD, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9) \
  virtual RETURN METHOD(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6, ARG7 arg7, ARG8 arg8, ARG9 arg9) { \
    return D_##METHOD##_fp(this , arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
  } \
  void D_set_##METHOD(RETURN (*fp) (CLASS* , ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9)) { \
    D_##METHOD##_fp = fp; \
  } \
  RETURN (*D_##METHOD##_fp) (CLASS*, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9); 

#define D_CPP_VIRTUAL_METHOD_SETTER_0(CLASS, METHOD, SETTER_NAME, RETURN) \
void SETTER_NAME(CLASS* c, RETURN (*fp) (CLASS*)) { \
  c->D_set_##METHOD(fp); \
}

#define D_CPP_VIRTUAL_METHOD_SETTER_1(CLASS, METHOD, SETTER_NAME, RETURN, ARG1) \
void SETTER_NAME(CLASS* c, RETURN (*fp) (CLASS*, ARG1)) { \
  c->D_set_##METHOD(fp); \
}

#define D_CPP_VIRTUAL_METHOD_SETTER_2(CLASS, METHOD, SETTER_NAME, RETURN, ARG1, ARG2) \
void SETTER_NAME(CLASS* c, RETURN (*fp) (CLASS*, ARG1, ARG2)) { \
  c->D_set_##METHOD(fp); \
}

#define D_CPP_VIRTUAL_METHOD_SETTER_3(CLASS, METHOD, SETTER_NAME, RETURN, ARG1, ARG2, ARG3) \
void SETTER_NAME(CLASS* c, RETURN (*fp) (CLASS*, ARG1, ARG2, ARG3)) { \
  c->D_set_##METHOD(fp); \
}

#define D_CPP_VIRTUAL_METHOD_SETTER_4(CLASS, METHOD, SETTER_NAME, RETURN, ARG1, ARG2, ARG3, ARG4) \
void SETTER_NAME(CLASS* c, RETURN (*fp) (CLASS*, ARG1, ARG2, ARG3, ARG4)) { \
  c->D_set_##METHOD(fp); \
}

#define D_CPP_VIRTUAL_METHOD_SETTER_5(CLASS, METHOD, SETTER_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5) \
void SETTER_NAME(CLASS* c, RETURN (*fp) (CLASS*, ARG1, ARG2, ARG3, ARG4, ARG5)) { \
  c->D_set_##METHOD(fp); \
}

#define D_CPP_VIRTUAL_METHOD_SETTER_6(CLASS, METHOD, SETTER_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) \
void SETTER_NAME(CLASS* c, RETURN (*fp) (CLASS*, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)) { \
  c->D_set_##METHOD(fp); \
}

#define D_CPP_VIRTUAL_METHOD_SETTER_7(CLASS, METHOD, SETTER_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) \
void SETTER_NAME(CLASS* c, RETURN (*fp) (CLASS*, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7)) { \
  c->D_set_##METHOD(fp); \
}

#define D_CPP_VIRTUAL_METHOD_SETTER_8(CLASS, METHOD, SETTER_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8) \
void SETTER_NAME(CLASS* c, RETURN (*fp) (CLASS*, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8)) { \
  c->D_set_##METHOD(fp); \
}

#define D_CPP_VIRTUAL_METHOD_SETTER_9(CLASS, METHOD, SETTER_NAME, RETURN, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9) \
void SETTER_NAME(CLASS* c, RETURN (*fp) (CLASS*, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9)) { \
  c->D_set_##METHOD(fp); \
}

#define D_CPP_BASE_CLASS_CLOSE() \
};

#define D_CPP_D_DECLARE(arg) ; 
