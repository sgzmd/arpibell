package com.sgzmd.doorbell;

import com.google.appengine.api.xmpp.*;
import com.google.appengine.repackaged.org.joda.time.DateTime;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.logging.Logger;

public class DoorbellServlet extends HttpServlet {
  private static final Logger LOG = Logger.getLogger(DoorbellServlet.class.getName());

  @Override
  protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    resp.getWriter().write("ACK");

    JID jid = new JID("sgzmd@jabber.ru");
    String messageBody = "Someone called at the door at " + new DateTime().toString();
    Message message = new MessageBuilder()
        .withRecipientJids(jid)
        .withBody(messageBody)
        .build();

    boolean messageSent = false;
    XMPPService xmpp = XMPPServiceFactory.getXMPPService();
    SendResponse status = xmpp.sendMessage(message);
    messageSent = (status.getStatusMap().get(jid) == SendResponse.Status.SUCCESS);

    LOG.info("Sent a message: " + message.toString() + ", message sent: " + messageSent);
  }
}
