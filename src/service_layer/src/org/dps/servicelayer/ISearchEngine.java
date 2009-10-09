package org.dps.servicelayer;

import java.util.List;
import java.util.Map;

public interface ISearchEngine {
	public static final String AUDIO_TITLE = "Audio.title";
	public static final String ARTIST_NAME = "Artist.name";
	
	//TODO: Add in sorting and pagination & remove session
	<T extends Object> List<T> search(Map<String, String> args_, Class<T> clazz_);
}
