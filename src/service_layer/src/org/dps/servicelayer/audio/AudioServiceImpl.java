package org.dps.servicelayer.audio;

import java.util.LinkedList;
import java.util.List;

import org.dps.servicelayer.ISearchEngine;
import org.dps.servicelayer.dto.Audio;
import org.dps.servicelayer.dto.IDTO;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.transaction.annotation.Transactional;

public class AudioServiceImpl implements AudioService {

//	private HibernateTemplate hibernateTemplate;
//	
//	public void setHibernateTemplate(HibernateTemplate hibernateTemplate) {
//		this.hibernateTemplate = hibernateTemplate;
//	}
	
	private final static Logger LOGGER = LoggerFactory.getLogger(AudioServiceImpl.class);
	private ISearchEngine searchEngine;
	private IDTO dto;
	
	public TestResponse testFunction(TestRequest params_) {
		return new TestResponse();
	}

	@Transactional
	public AudioSearchResponse search(AudioSearchRequest params_) {
		// TODO Auto-generated method stub
		
		//List audioList = hibernateTemplate.find("from Audio where title=?",params.get_title());
		
		AudioSearchResponse response = new AudioSearchResponse(params_);
		
		List<Audio> audios = searchEngine.search(params_.getSearchKeysAsMap(), Audio.class);
		List<AudioSummary> audioSummary = new LinkedList<AudioSummary>();
		for (Audio audio : audios) {
			LOGGER.info("Constructing Summary: ", audio.getFileID());
			audioSummary.add(new AudioSummary(audio));
		}
			
		response.setAudios(audioSummary);			
		return response;
	}

	@Transactional
	public GetAudioResponse getAudio(GetAudioRequest params_) {
		GetAudioResponse response = new GetAudioResponse(params_);
		Audio track = dto.getAudio(params_.getAudioID());	
		track.makeSafe();
		response.setAudio(track);
		return response;
	}

	public void setSearchEngine(ISearchEngine searchEngine) {
		this.searchEngine = searchEngine;
	}
	
	public void setDto(IDTO dto_) {
		dto = dto_;
	}

}
