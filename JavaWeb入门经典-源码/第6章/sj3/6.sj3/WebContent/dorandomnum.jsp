<%@ page contentType="text/html;charset=gb2312"%>
<jsp:useBean id="myrandom" class="com.wgh.random.RanDom"/>
<%
  String strnum=request.getParameter("number");
  if(strnum==null)
	  strnum="0";
  int num=0;
  try{
	  num=Integer.parseInt(strnum);
  }catch(Exception e){num=0;}
  myrandom.setNumber(num);
  myrandom.makeChecknum();
%>
<html>
  <head>
    <title>�������ָ��λ������֤��</title>
    <link rel="stylesheet" type="text/css" href="css/style.css">
  </head>
  <body>
   <center>
       <table style="margin-top:200" width="250" border="1" cellpadding="0" cellspacing="0" bordercolor="black" bordercolorlight="black" bordercolordark="white">
         <tr bgcolor="lightgrey" height="30">
            <td align="center">���ɵ���֤��</td>
         </tr>
         <tr height="50">
            <td align="center">
              ��֤���λ����<%=myrandom.getNumber() %>
              <br>
              ���ɵ���֤�룺<%=myrandom.getChecknum()%>
            </td>
         </tr>
       </table>
       <a href="index.jsp">[����]</a>
   </center>
  </body>
</html>