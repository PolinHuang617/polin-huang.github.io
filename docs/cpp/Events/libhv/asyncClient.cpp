#include <hv/requests.h>
#include <hv/hthread.h>

using namespace hv;

static void testHttpAsyncClient(bool& finished)
{
    printf("test http async client request thread tid=%ld\n", hv_gettid());

    HttpRequestPtr req(new HttpRequest);
    req->method = HTTP_POST;
    req->url = "127.0.0.1:1234/echo";
    req->headers["Connection"] = "keep-alive";
    req->body = "this is an async request.";
    req->timeout = 10;
    http_client_send_async(req, [&finished](const HttpResponsePtr& resp)
    {
        printf("test http async client response thread tid=%ld\n", hv_gettid());
        if (resp == NULL)
        {
            printf("request failed!\n");
        }
        else
        {
            printf("%d %s\r\n", resp->status_code, resp->status_message());
            printf("%s\n", resp->body.c_str());
        }
        finished = true;
    });
}

auto main(int argc, char* argv[]) -> int
{
    bool finished = false;
    testHttpAsyncClient(finished);

    while (!finished)
    {
        hv_delay(100);
    }

    return EXIT_SUCCESS;
}