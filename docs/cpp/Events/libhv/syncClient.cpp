#include <hv/requests.h>
#include <hv/http_client.h>

auto main(int argc, char* argv[]) -> int
{
    auto response = requests::get("http://www.example.com");
    if (response == NULL)
    {
         printf("request failed\n");
    }
    else
    {
         printf("%d %s\r\n", response->status_code, response->status_message());
         printf("%s\n", response->body.c_str());
    }

    response = requests::post("http://localhost:1234/echo", "hello world!");
    // response = requests::get("localhost:1234/ping");
    if (response == NULL)
    {
        printf("request failed\n");
    }
    else
    {
        printf("%d %s\r\n", response->status_code, response->status_message());
        printf("%s\n", response->body.c_str());
    }

    return EXIT_SUCCESS;
}
