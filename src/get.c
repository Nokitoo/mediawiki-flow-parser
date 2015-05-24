/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <string.h> */
/* #include <curl/curl.h> */

/* struct		MemoryStruct */
/* { */
/*   char		*memory; */
/*   size_t	size; */
/* }; */

/* static size_t	WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) */
/* { */
/*   size_t realsize = size * nmemb; */
/*   struct MemoryStruct *mem = (struct MemoryStruct *)userp; */
/*   mem->memory = realloc(mem->memory, mem->size + realsize + 1); */
/*   if (mem->memory == NULL) */
/*     { */
/*     printf("not enough memory (realloc returned NULL)\n"); */
/*     return (0); */
/*   } */
/*   memcpy(&(mem->memory[mem->size]), contents, realsize); */
/*   mem->size += realsize; */
/*   mem->memory[mem->size] = 0; */
/*   return (realsize); */
/* } */

/* int		get(char *url) */
/* { */
/*   CURL		*curl_handle; */
/*   CURLcode	res; */

/*   struct MemoryStruct chunk; */
/*   chunk.memory = malloc(1); */
/*   chunk.size = 0; */
/*   curl_global_init(CURL_GLOBAL_ALL); */
/*   curl_handle = curl_easy_init(); */
/*   curl_easy_setopt(curl_handle, CURLOPT_URL, url); */
/*   curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback); */
/*   curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk); */
/*   curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0"); */
/*   if ((res = curl_easy_perform(curl_handle)) != CURLE_OK) */
/*     { */
/*       fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res)); */
/*       return (1); */
/*     } */
/*   printf("%s\n", chunk.memory); */
/*   curl_easy_cleanup(curl_handle); */
/*   free(chunk.memory); */
/*   curl_global_cleanup(); */
/*   return (0); */
/* } */
