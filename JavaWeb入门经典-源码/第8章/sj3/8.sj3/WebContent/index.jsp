<%@ page language="java" import="java.util.*" pageEncoding="GB18030"%>
<html>
  <head>
    <title>Ӧ��EL���ʽ�ж��û��Ƿ��¼</title>
  </head>
  
  <body>
    ${empty sessionScope.user ? "����û�е�¼<a href='login.jsp'>��¼</a>" : sessionScope.user}
	${!empty sessionScope.user ? "��ӭ����������վ[<a href='logout.jsp'>�˳�</a>]":""}
  </body>
</html>
