package org.dps.servicelayer.dto;

import java.util.HashSet;
import java.util.Set;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.JoinTable;
import javax.persistence.ManyToMany;
import javax.persistence.Table;

@Entity
@Table(name="user")
public class User extends Audit{

	@Column(name="user_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long userID;
	
	@Column(name="username")
	private String username;
	
	@Column(name="enabled")
	private Boolean enabled;
	
	@Column(name="ghost")
	private Boolean ghost;
	
	@ManyToMany(targetEntity=Group.class, cascade={CascadeType.PERSIST, CascadeType.MERGE})
	@JoinTable(name="usergroup", 
			joinColumns=@JoinColumn(name="user_id"), 
			inverseJoinColumns=@JoinColumn(name="group_id"))
	private Set<Group> groups = new HashSet<Group>();

	public String toString() {
		return userID + ":" + username;
	}
	
	/**
	 * @return the userID
	 */
	public Long getUserID() {
		return userID;
	}

	/**
	 * @param userID the userID to set
	 */
	public void setUserID(Long userID) {
		this.userID = userID;
	}

	/**
	 * @return the username
	 */
	public String getUsername() {
		return username;
	}

	/**
	 * @param username the username to set
	 */
	public void setUsername(String username) {
		this.username = username;
	}

	/**
	 * @return the enabled
	 */
	public Boolean getEnabled() {
		return enabled;
	}

	/**
	 * @param enabled the enabled to set
	 */
	public void setEnabled(Boolean enabled) {
		this.enabled = enabled;
	}

	/**
	 * @return the ghost
	 */
	public Boolean getGhost() {
		return ghost;
	}

	/**
	 * @param ghost the ghost to set
	 */
	public void setGhost(Boolean ghost) {
		this.ghost = ghost;
	}

	/**
	 * @return the groups
	 */
	public Set<Group> getGroups() {
		return groups;
	}

	/**
	 * @param groups the groups to set
	 */
	public void setGroups(Set<Group> groups) {
		this.groups = groups;
	}
	
	
}
