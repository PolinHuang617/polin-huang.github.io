#include <hv/HttpServer.h>

auto main(int argc, char** argv) -> int
{
    HttpService router;
    router.GET("/ping", [](HttpRequest* req, HttpResponse* resp)
    {
        return resp->String("pong");
    });
    router.GET("/data", [](HttpRequest* req, HttpResponse* resp)
    {
        static char data[] = "0123456789";
        return resp->Data(data, sizeof(data));
    });
    router.GET("/paths", [&router](HttpRequest* req, HttpResponse* resp)
    {
        return resp->Json(router.Paths());
    });
    router.POST("/echo", [](const HttpContextPtr& context)
    {
        return context->send(context->body(), context->type());
    });
    http_server_t server;
    server.port = 1234;
    server.service = &router;
    http_server_run(&server);

    return EXIT_SUCCESS;
}