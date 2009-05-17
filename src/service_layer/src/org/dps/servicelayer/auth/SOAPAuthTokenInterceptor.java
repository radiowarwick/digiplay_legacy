package org.dps.servicelayer.auth;

import java.util.List;
import java.util.Map;

import org.apache.cxf.binding.soap.Soap11;
import org.apache.cxf.binding.soap.Soap12;
import org.apache.cxf.binding.soap.SoapMessage;
import org.apache.cxf.binding.soap.interceptor.AbstractSoapInterceptor;
import org.apache.cxf.binding.soap.interceptor.EndpointSelectionInterceptor;
import org.apache.cxf.binding.soap.interceptor.ReadHeadersInterceptor;
import org.apache.cxf.helpers.CastUtils;
import org.apache.cxf.interceptor.Fault;
import org.apache.cxf.message.Message;
import org.apache.cxf.phase.Phase;

public class SOAPAuthTokenInterceptor extends AbstractSoapInterceptor {

	public SOAPAuthTokenInterceptor() {
		super(Phase.READ);
        addAfter(ReadHeadersInterceptor.class.getName());
        addAfter(EndpointSelectionInterceptor.class.getName());
	}
	
	public void handleMessage(SoapMessage message) throws Fault {
		if (message.getVersion() instanceof Soap11) {
            Map<String, List<String>> headers = CastUtils.cast((Map)message.get(Message.PROTOCOL_HEADERS));
            if (headers != null) {
                List<String> sa = headers.get("SOAPAction");
                if (sa != null && sa.size() > 0) {
                    String action = sa.get(0);
                    if (action.startsWith("\"")) {
                        action = action.substring(1, action.length() - 1);
                    }
                    //getAndSetOperation(message, action);
                }
            }
        } else if (message.getVersion() instanceof Soap12) {
          //...........
        }

	}

}
