package org.dps.servicelayer.audio;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebResult;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;

@WebService(targetNamespace = "http://radio.warwick.ac.uk/dps/audio", name = "AudioService")
@SOAPBinding(parameterStyle = SOAPBinding.ParameterStyle.BARE)
public interface AudioService {

	@WebResult(name = "testFunction", targetNamespace = "http://radio.warwick.ac.uk/dps/audio", partName = "response")
    @WebMethod
   public TestResponse testFunction(
		   @WebParam(partName = "parameters", name = "testRequest", targetNamespace = "http://radio.warwick.ac.uk/dps/audio")
		   TestRequest params);

}