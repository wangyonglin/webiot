#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <network/server.h>
#include <network/restful.h>

void ____callback(struct network_client_s *client, uint8_t *data, int len);
int main(int argc, char *argv[])
{

	int rc = 0;
	wangyonglin(argc, argv);

	network_restful_t restful;
	network_restful_conf(&restful);
	network_restful_bind(&restful);
	network_restful_run(&restful);
	netwrok_restful_close(&restful);

	
	return rc;
}
void ____callback(struct network_client_s *client, uint8_t *data, int len)
{
	wangyonglin_log_info("[%s:%d]%s-%d", inet_ntoa((struct in_addr)client->addr.sin_addr), client->addr.sin_port, data, len);
}