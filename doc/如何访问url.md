* ��curl�����˷�װ<br/>

```
// ����_httpָ��
ngl::_http* lhttp = ngl::manage_curl::make_http();
// ���÷���ģʽ [ENUM_MODE_HTTP/ENUM_MODE_HTTPS]
ngl::manage_curl::set_mode(*lhttp, ngl::ENUM_MODE_HTTPS);
// ���÷������� [ENUM_TYPE_POST/ENUM_TYPE_GET]
ngl::manage_curl::set_type(*lhttp, ngl::ENUM_TYPE_POST);
// ���÷��ʵ�ַ
ngl::manage_curl::set_url(*lhttp, "https://xxxxx/external/index/auth");

// ���ò���
std::string lparm;
ngl::manage_curl::param(lparm, "game_id", 45);
ngl::manage_curl::param(lparm, "sign", "13d89fa2af33de479deaf48da67ba01f");
ngl::manage_curl::param(lparm, "timestamp", "1693920175");
ngl::manage_curl::param(lparm, "token", "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJmaWZ1bi5nYW1lcyIsImF1ZCI6ImZpZnVuLmdhbWVzIiwiaWF0IjoxNjkzOTIwMTQ0LCJleHAiOjE2OTY1MTIxNDQsIm5iZiI6MTY5MzkyMDE0NCwicGxhdGZvcm1fdWlkIjoyOTY5NDQ4LCJwbGF0Zm9ybV9hY2NvdW50Ijoiemh1Z29uZzMiLCJnYW1lX2lkIjo0NSwiZ2FtZV91aWQiOjQzNjg1MDYsInV1aWQiOiJlZjA5Yzg1MmQ4ZjRkYWE5Y2JiNGY2MjM1MjBlNjQ1OSJ9.nXnFg3gu1DdPVWtvcq4u6SmXNse0fUQ3OyMr3QvN0JE");
ngl::manage_curl::param(lparm, "uid", "2969448");

// ���÷��ʺ󷵻صĻص�
ngl::manage_curl::set_callback(*lhttp, [&lbool](int anum, ngl::_http& aparm)
	{
		std::cout << aparm.m_recvdata << std::endl;
		lbool = false;
	});

// ���з���
ngl::manage_curl::getInstance().send(lhttp);

```
