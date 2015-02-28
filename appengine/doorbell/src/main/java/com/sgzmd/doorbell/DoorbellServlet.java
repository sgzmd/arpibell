package com.sgzmd.doorbell;

import com.google.appengine.api.xmpp.*;
import com.google.appengine.repackaged.org.joda.time.DateTime;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

public class DoorbellServlet extends HttpServlet {
  private static final Logger LOG = Logger.getLogger(DoorbellServlet.class.getName());
  private final String id;

  public DoorbellServlet() {
    Properties properties = new Properties();
    try {
      properties.load(new FileInputStream("WEB-INF/settings.properties"));
      this.id = properties.getProperty("key");
    } catch (IOException e) {
      LOG.log(Level.SEVERE, "Error loading properties file", e);
      throw new RuntimeException(e);
    }
  }

  @Override
  protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    resp.getWriter().write("ACK");

    if (req.getParameter("id") != null && req.getParameter("id").equals("klajk3812--041nkszpow3")) {
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
    } else {
      LOG.info("Unauthorized request: " + req.getRequestURI());
    }
  }
}
