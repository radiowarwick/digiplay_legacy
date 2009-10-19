package org.dps.servicelayer.audio;

import java.util.LinkedList;
import java.util.List;

import org.dps.servicelayer.ISearchEngine;
import org.dps.servicelayer.dto.Album;
import org.dps.servicelayer.dto.Artist;
import org.dps.servicelayer.dto.Audio;
import org.dps.servicelayer.dto.Constants;
import org.dps.servicelayer.dto.File;
import org.dps.servicelayer.dto.IDTO;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.transaction.annotation.Transactional;

public class AudioServiceImpl implements AudioService {
	
	/**
	 * The Logger.
	 */
	private final static Logger LOGGER = LoggerFactory.getLogger(AudioServiceImpl.class);
	/**
	 * The search engine.
	 */
	private ISearchEngine searchEngine;
	/**
	 * Usefull dto access object.
	 */
	private IDTO dto;
	
	@Transactional
	public AudioSearchResponse search(AudioSearchRequest params_) {
		AudioSearchResponse response = new AudioSearchResponse(params_);
		
		List<Audio> audios = searchEngine.search(params_.getSearchKeysAsMap(), Audio.class);
		List<AudioSummary> audioSummary = new LinkedList<AudioSummary>();
		for (Audio audio : audios) {
			LOGGER.info("Constructing Summary: {}", audio.getFileID());
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
	
	@Transactional
	public AddAudioResponse addAudio(AddAudioRequest params_) {
		AddAudioResponse response = new AddAudioResponse(params_);
		Audio audio = params_.getAudio();
		if(audio == null) {
			//TODO Throw error.
			LOGGER.error("You must specify an audio");
		}
		//TODO A whole lot more checking...
		Audio newAudio = dto.saveOrUpdate(audio);
		response.setAudio(newAudio);
		return response;
	}

	@Transactional
	public DeleteAudioResponse deleteAudio(DeleteAudioRequest params_) {
		//Instead of deleting, just move to the bin.
		DeleteAudioResponse response = new DeleteAudioResponse(params_);
		File bin = dto.getFile(Constants.DEFAULT_FILE_SYSTEM_BIN);
		if(bin == null) {
			//TODO Throw error.
			LOGGER.error("Unable to locate bin: {}", Constants.DEFAULT_FILE_SYSTEM_BIN);
		}
		Audio audio = dto.getAudio(params_.getAudioID());
		if(audio == null) {
			//TODO Throw error.
			LOGGER.error("You must specify an audio");
		}
		audio.addChild(bin);
		dto.saveOrUpdate(audio);
		return response;
	}
	
	@Transactional
	public AddArtistResponse addArtist(AddArtistRequest params_) {
		AddArtistResponse response = new AddArtistResponse(params_);
		Artist artist = params_.getArtist();
		if(artist == null) {
			//TODO Throw error.
			LOGGER.error("You must specify an artist");
		}
		if(artist.getName() == null) {
			//TODO Throw error.
			LOGGER.error("You must specify an artist's name");
		}
		Artist newArtist = dto.getArtist(artist.getName());
		if(newArtist == null) {
			newArtist = dto.saveOrUpdate(artist);
		}
		response.setArtist(newArtist);
		return response;
	}
	
	@Transactional
	public AddAudioArtistResponse addAudioArtist(AddAudioArtistRequest params_) {
		AddAudioArtistResponse response = new AddAudioArtistResponse(params_);
		Audio audio = dto.getAudio(params_.getAudioID());
		if(audio == null) {
			//TODO Throw error.
			LOGGER.error("Unable to find audio for ID: {}", params_.getAudioID());
		}
		Artist artist = dto.getArtist(params_.getArtistID());
		if(artist == null) {
			//TODO Throw error.
			LOGGER.error("Unable to find artist for ID: {}", params_.getArtistID());
		}
		//FIXME: actually add the artist!
		audio.getArtists().add(artist);
		artist.getAudios().add(audio);
		dto.saveOrUpdate(audio);
		dto.saveOrUpdate(artist);
		audio.makeSafe();
		response.setAudio(audio);
		
		return response;
	}
	
	@Transactional
	public AddAlbumResponse addAlbum(AddAlbumRequest params_) {
		AddAlbumResponse response = new AddAlbumResponse(params_);
		Album album = params_.getAlbum();
		if(album == null) {
			//TODO Throw error.
			LOGGER.error("You must specify an album");
		}
		if(album.getName() == null) {
			//TODO Throw error.
			LOGGER.error("You must specify an album's name");
		}
		Album newAlbum = dto.getAlbum(album.getName());
		if(newAlbum == null) {
			newAlbum = dto.saveOrUpdate(album);
		}
		response.setAlbum(newAlbum);
		return response;
	}

	@Transactional
	public AddAudioAlbumResponse addAudioAlbum(AddAudioAlbumRequest params_) {
		AddAudioAlbumResponse response = new AddAudioAlbumResponse(params_);
		Audio audio = dto.getAudio(params_.getAudioID());
		if(audio == null) {
			//TODO Throw error.
			LOGGER.error("Unable to find audio for ID: {}", params_.getAudioID());
		}
		Album album = dto.getAlbum(params_.getAlbumID());
		if(album == null) {
			//TODO Throw error.
			LOGGER.error("Unable to find artist for ID: {}", params_.getAlbumID());
		}
		//FIXME: actually add the album!
		audio.getAlbums().add(album);
		album.getAudio().add(audio);
		dto.saveOrUpdate(audio);
		dto.saveOrUpdate(album);
		audio.makeSafe();
		response.setAudio(audio);
		
		return response;
	}
	
	@Transactional
	public AddAudioCommentResponse addAudioComment(
			AddAudioCommentRequest params_) {
		AddAudioCommentResponse response = new AddAudioCommentResponse(params_);
		Audio audio = dto.getAudio(params_.getAudioID());
		if(audio == null) {
			//TODO Throw error.
			LOGGER.error("Unable to find audio for ID: {}", params_.getAudioID());
		}
		//TODO: Add comment - should this be a dto command or a manual command with a save??
		return response;
	}

//
// Spring members.
//
	public void setSearchEngine(ISearchEngine searchEngine) {
		this.searchEngine = searchEngine;
	}
	
	public void setDto(IDTO dto_) {
		dto = dto_;
	}

}
