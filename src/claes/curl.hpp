#pragma once

#include <iostream>
#include "curl/curl.h"
#include "claes/error.hpp"

namespace claes {  
  using namespace std;

  struct Stack;
  struct VM;

  struct Curl {
    struct Imp {
      CURL *handle;
      int ref_count = 1;
      
      Imp(): handle(curl_easy_init()) { }

      ~Imp() {
	curl_easy_cleanup(handle);
      }

      void deref() {
	if (!ref_count--) {
	  delete this;
	}
      }
    };

    struct Response {
      array<char, 4096> body;
      size_t len = 0;
    };

    static size_t write_callback(char *ptr, 
				 size_t size, 
				 size_t nmemb, 
				 void *userdata) {
      size_t total_size = size * nmemb;
      auto response = (Response *)userdata;
      memcpy(response->body.data(), ptr, total_size);
      response->len += total_size;
      return total_size;
    }

    Imp *imp;

    Curl(): imp(new Imp()) {}
    
    Curl(const Curl &source): imp(source.imp) {
      imp->ref_count++;
    }

    ~Curl() {
      imp->deref();
    }
    
    const Curl &operator=(const Curl &source) {
      imp->deref();
      imp = source.imp;
      imp->ref_count++;
      return *this;
    }

    E call(VM &vm, Stack &stack, const int arity, const Loc &loc) const;
  };

  inline bool operator==(const Curl &left, const Curl &right) {
    return left.imp == right.imp;
  }

  inline strong_ordering operator<=>(const Curl &left, const Curl &right) {
    return left.imp <=> right.imp;
  }

  inline ostream &operator<<(ostream &out, const Curl &c) {
    out << "(Curl " << c.imp << ')';
    return out;
  }

}
