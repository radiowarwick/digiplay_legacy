package org.dps.servicelayer.audio;

import org.dps.servicelayer.ISearchEngine;
import org.junit.Test;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;


public class AudioServiceTest extends AbstractDependencyInjectionSpringContextTests {
	
	private AudioServiceImpl audioService;
	
	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/audio/test-audio-spring-config.xml" };
	}
	
	public void setAudioService(AudioServiceImpl audioService) {
		this.audioService = audioService;
	}

	@Test
	public void testASimpleRequest() {
		AudioSearchRequest asr = new AudioSearchRequest();
		asr.addSearchKey(ISearchEngine.AUDIO_TITLE, "Hello");
		AudioSearchResponse response = audioService.search(asr);
		assertNotNull(response);
		assertNotNull(response.getAudios());
		assertEquals(1, response.getAudios().size());
	}
	
	@Test
	public void testAMultiValueRequest() {
		AudioSearchRequest asr = new AudioSearchRequest();
		asr.addSearchKey(ISearchEngine.AUDIO_TITLE, "Hello");
		asr.addSearchKey(ISearchEngine.ARTIST_NAME, "Mr Gough");
		AudioSearchResponse response = audioService.search(asr);
		assertNotNull(response);
		assertNotNull(response.getAudios());
		assertEquals(1, response.getAudios().size());
	}
	

}
