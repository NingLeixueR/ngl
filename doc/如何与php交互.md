* ��php������Ҫ����actor_gm<br/>
������Ҫͨ��json<br/>
```
/*
   ��Ҫ���͸����������ֶΰ���
  actor_name   ָ��actor������   ��������
  actor_id     �����ƶ�actor     �ǵ�������
  operator     �ƶ��������ͣ��Զ����ַ�����
  data         ��ѡ����
*/
����ӹ���Ϊ��
$arr = array(
 'actor_name' => 'ACTOR_NOTICE',
 'operator' => 'add_notice',
 'data' => array(
   'id' => '-1',
   'notice' => $_POST['notice'],
   'starttime' => intval($_POST['starttime']),
   'finishtime' => intval($_POST['finishtime']),
 )
);

// ��ʱ����ֻ��Ҫ�ڡ�bool actor_notice::handle(message<mforward<np_gm>>& adata)��
// ʵ�ֶ�'add_notice'�Ĵ���
```
