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

	@WebResult(name = "search", targetNamespace = Namespaces.AUDIO, partName = "response")
	@WebMethod
	public AudioSearchResponse search(
			@WebParam(partName = "parameters", name = "searchRequest", targetNamespace = Namespaces.AUDIO) 
			AudioSearchRequest params_);
	
	@WebResult(name = "getAudio", targetNamespace = Namespaces.AUDIO, partName = "response")
	@WebMethod
	public GetAudioResponse getAudio(
			@WebParam(partName = "parameters", name = "getAudioRequest", targetNamespace = Namespaces.AUDIO) 
			GetAudioRequest params_);
	
	@WebResult(name = "addAudioComment", targetNamespace = Namespaces.AUDIO, partName = "response")
	@WebMethod
	public AddAudioCommentResponse addAudioComment(
			@WebParam(partName="parameters", name="addAudioCommentRequest", targetNamespace = Namespaces.AUDIO)
			AddAudioCommentRequest params_);
	
	@WebResult(name = "addArtist", targetNamespace = Namespaces.AUDIO, partName = "response")
	@WebMethod
	public AddArtistResponse addArtist(
			@WebParam(partName="parameters", name="addArtistRequest", targetNamespace = Namespaces.AUDIO)
			AddArtistRequest params_);
	
	@WebResult(name = "addAudioArtist", targetNamespace = Namespaces.AUDIO, partName = "response")
	@WebMethod
	public AddAudioArtistResponse addAudioArtist(
			@WebParam(partName="parameters", name="addAudioArtistRequest", targetNamespace = Namespaces.AUDIO)
			AddAudioArtistRequest params_);

}