#include "claes/cell.hpp"
#include "claes/types/curl.hpp"
#include "claes/types/string.hpp"
#include "claes/stack.hpp"
#include "claes/vm.hpp"

namespace claes::types {
  E Curl::call(VM &vm, 
	       Stack &stack, 
	       int arity,
	       const claes::Loc &loc) const {
    stack.push(types::Curl::get(), claes::Curl());
    return nullopt;
  }

  E Curl::call(Cell &target, 
	       VM &vm, 
	       Stack &stack, 
	       int arity,
	       bool recursive,
	       const claes::Loc &loc) const {
    const auto data = stack.pop();
    const auto ct = stack.pop().as(String::get());
    const auto url = stack.pop().as(String::get());
   
    auto c = target.as(get()).imp->handle;
    curl_easy_setopt(c, CURLOPT_URL, url.c_str());
    curl_easy_setopt(c, CURLOPT_POST, 1L);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, to_string("Content-Type: ", ct).c_str());
    curl_easy_setopt(c, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(c, CURLOPT_POSTFIELDS, data.as(String::get()).data());

    Response response;
    curl_easy_setopt(c, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, claes::Curl::write_callback);

    if (const auto res = curl_easy_perform(c); res != CURLE_OK) {
      return Error(loc, "Failed sending request: ", curl_easy_strerror(res));
    }

    stack.push(String::get(), 
	       string(response.body.begin(), response.body.begin() + response.len));

    curl_slist_free_all(headers);
    return nullopt;
  };
  
  void Curl::dump(const Cell &value, ostream &out) const {
    out << value.as(get());
  }

  bool Curl::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
}
