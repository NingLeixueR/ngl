* д����־��BI(����)<br/>
��[nlog.h]�ж����˺ܶ��<br/>
������־����������<br/>

```
enum ELOG
{
  ELOG_DEBUG,   // ������Ϣ
  ELOG_INFO,    // ��ӡ
  ELOG_WARN,    // ����
  ELOG_ERROR,   // ����
  ELOG_NONE,    // ��
};
```

������־�洢λ������<br/>
����������<br/>

��־��ӡ�ֱ������º궨��<br/>

```
// [������Ϣ]���ش�ӡ
# define LogDebug(FORMAT,...)			dlogmsg(ngl::ELOG_DEBUG, false, FORMAT,##__VA_ARGS__)
// [������Ϣ]���ش�ӡ
# define LogError(FORMAT,...)			dlogmsg(ngl::ELOG_ERROR, false, FORMAT,##__VA_ARGS__)
// [��ӡ��Ϣ]���ش�ӡ
# define LogInfo(FORMAT,...)			dlogmsg(ngl::ELOG_INFO, false,FORMAT, ##__VA_ARGS__)
// [������Ϣ]���ش�ӡ
# define LogWarn(FORMAT,...)			dlogmsg(ngl::ELOG_WARN, false, FORMAT,##__VA_ARGS__)
// [������Ϣ]�����ӡ
#define LogLocalDebug(FORMAT,...)		dlogmsg(ngl::ELOG_DEBUG, true, FORMAT,##__VA_ARGS__)
// [������Ϣ]�����ӡ
#define LogLocalError(FORMAT,...)		dlogmsg(ngl::ELOG_ERROR, true, FORMAT,##__VA_ARGS__)
// [��ӡ��Ϣ]�����ӡ
#define LogLocalInfo(FORMAT,...)		dlogmsg(ngl::ELOG_INFO, true,FORMAT,##__VA_ARGS__)
// [������Ϣ]�����ӡ
#define LogLocalWarn(FORMAT,...)		dlogmsg(ngl::ELOG_WARN, true, FORMAT,##__VA_ARGS__)
```
ʹ�÷���<br/>
```
LogDebug("[������Ϣ]���ش�ӡ")                // �����[������Ϣ]���ش�ӡ
LogDebug("[%]%","������Ϣ",���ش�ӡ)          // �����[������Ϣ]���ش�ӡ
LogDebug("[%]%-%","������Ϣ",���ش�ӡ��1989)  // �����[������Ϣ]���ش�ӡ-1989
```
��try...catchҲ�����˷�װ<br/>
```
Try
{
  xxxx
}Catch
```
�������в���Ὣ������Ϣ�Զ���ӡ������̨���ļ�<br/>

˵˵������������־������<br/>
����ʵ�ֶ��Էֱ��Ǵ�������actor_log����<br/>
ÿ�����̶���һ��actor_log��������actor_log��guidΪnguid::make(ACTOR_LOG, tab_self_area, ELOG_LOCAL);<br/>
��Ȼ����actor_log�Ϳ��Բ���������һ�����̻��ߵ���Ϊ�䴴��һ������,��guidΪnguid::make(ACTOR_LOG, tab_self_area, ELOG_NETWORK);<br/>
