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
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlTransient;

@Entity
@Table(name="user")
@XmlAccessorType(XmlAccessType.NONE)
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
	
	/**
	 * @return the userID
	 */
	@XmlElement(required = true)
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
	@XmlElement(required = true)
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
	@XmlElement(required = true)
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
	@XmlElement(required = true)
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
	@XmlTransient
	public Set<Group> getGroups() {
		return groups;
	}
	/**
	 * @param groups the groups to set
	 */
	public void setGroups(Set<Group> groups) {
		this.groups = groups;
	}
	
	public String toString() {
		return userID + ":" + username;
	}
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((userID == null) ? 0 : userID.hashCode());
		return result;
	}
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		User other = (User) obj;
		if (userID == null) {
			if (other.userID != null)
				return false;
		} else if (!userID.equals(other.userID))
			return false;
		return true;
	}
	
}
