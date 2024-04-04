#ifdef USE_CURL

#include "claes/curl.hpp"
#include "claes/stack.hpp"
#include "claes/types/string.hpp"

namespace claes {
  E Curl::call(VM &vm, Stack &stack, const int arity, const Loc &loc) const {
    const auto data = stack.pop();
    const auto ct = stack.pop().as(types::String::get());
    const auto url = stack.pop().as(types::String::get());
    
    auto c = imp->handle;
    curl_easy_setopt(c, CURLOPT_URL, url.c_str());
    curl_easy_setopt(c, CURLOPT_POST, 1L);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, to_string("Content-Type: ", ct).c_str());
    curl_easy_setopt(c, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(c, CURLOPT_POSTFIELDS, data.as(types::String::get()).data());
    
    Response response;
    curl_easy_setopt(c, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, write_callback);
    
    if (const auto res = curl_easy_perform(c); res != CURLE_OK) {
      return Error(loc, "Failed sending request: ", curl_easy_strerror(res));
    }
    
    stack.push(types::String::get(), 
	       string(response.body.begin(), response.body.begin() + response.len));
    
    curl_slist_free_all(headers);
    return nullopt;
  }
}

#endif
