package org.dps.servicelayer.audio;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebResult;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;

import org.dps.servicelayer.Namespaces;

@WebService(targetNamespace = Namespaces.AUDIO, name = "AudioService")
@SOAPBinding(parameterStyle = SOAPBinding.ParameterStyle.BARE)
public interface AudioService {

	@WebResult(name = "testFunction", targetNamespace = Namespaces.AUDIO, partName = "response")
	@WebMethod
	public TestResponse testFunction(
			@WebParam(partName = "parameters", name = "testRequest", targetNamespace = Namespaces.AUDIO) TestRequest params);

	@WebResult(name = "search", targetNamespace = Namespaces.AUDIO, partName = "response")
	@WebMethod
	public AudioSearchResponse search(@WebParam(partName = "parameters", name = "searchRequest", 
			targetNamespace = Namespaces.AUDIO) AudioSearchRequest params);
	
	@WebResult(name = "getAudio", targetNamespace = Namespaces.AUDIO, partName = "response")
	@WebMethod
	public GetAudioResponse getAudio(@WebParam(partName = "parameters", name = "getAudioRequest", 
			targetNamespace = Namespaces.AUDIO) GetAudioRequest params);

}